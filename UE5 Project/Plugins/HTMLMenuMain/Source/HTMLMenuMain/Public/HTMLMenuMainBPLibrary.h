// Copyright 2018-2020 David Romanski (Socke). All Rights Reserved.

#pragma once

#include "HTMLMenuMain.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "HTMLMenuMainBPLibrary.generated.h"


class FHtmlMenuWebsocketClientThread;
class FHtmlMenuWebsocketServerThread;


UCLASS()
class HTMLMENUMAIN_API UHTMLMenuMainBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	static UHTMLMenuMainBPLibrary* HTMLMenuMainBPLibrary;
	static UHTMLMenuMainBPLibrary* getHTMLMenuMainBPLibrary();
	   
	void initWebsocketServer(UHTMLMenu* menu);
	void callJavascript(FString javascript);
	void handleWebsocketData(FString& data);
	UHTMLMenu* getMenu();
	void setInConnectionProcess(bool connectionp);

	//UFUNCTION(BlueprintCallable, Category = "HTML Menu")
	//	static void testAbc();

	//void testaaa();

private:
	class FHtmlMenuWebsocketServerThread* websocketServerThread = nullptr;
	UHTMLMenu* menu = nullptr;
	bool isInConnectionProcess = false;
};

/*********************************************** WEBSOCKET MINI SERVER ***********************************************/
/*CLIENT get Data asynchronous Thread*/
class FHtmlMenuWebsocketClientThread : public FRunnable {

public:
	FHtmlMenuWebsocketClientThread(FSocket* clientSocketP, UHTMLMenuMainBPLibrary * mainlibP) :
		clientSocket(clientSocketP),
		mainlib(mainlibP) {
		FString threadName = "FHtmlMenuWebsocketClientThread_" + FGuid::NewGuid().ToString();
		thread = FRunnableThread::Create(this, *threadName, 0, EThreadPriority::TPri_Normal);
	}

	virtual uint32 Run() override {

		if (mainlib != nullptr)
			mainlib->setInConnectionProcess(false);

		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("HTMLMenu: 20"));*/

			//UE_LOG(LogTemp, Display, TEXT("TCP Connected: %s:%i"), *session.ip, session.port);
		uint32 DataSize;
		FArrayReaderPtr Datagram = MakeShareable(new FArrayReader(true));
		while (run && clientSocket != nullptr) {
			//ESocketConnectionState::SCS_Connected does not work https://issues.unrealengine.com/issue/UE-27542
			//Compare ticks is a workaround to get a disconnect. clientSocket->Wait() stop working after disconnect. (Another bug?)
			//If it doesn't wait any longer, ticks1 and ticks2 should be the same == disconnect.
			int64 ticks1 = FDateTime::Now().GetTicks();
			clientSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(0.1));
			int64 ticks2 = FDateTime::Now().GetTicks();
			bool hasData = clientSocket->HasPendingData(DataSize);
			if (!hasData && ticks1 == ticks2)
				break;
			if (hasData) {

				Datagram->Empty();
				Datagram->SetNumUninitialized(DataSize);
				int32 BytesRead = 0;
				if (clientSocket->Recv(Datagram->GetData(), Datagram->Num(), BytesRead)) {

					if (needHandshake) {

						FString recvMessage;
						char* Data = (char*)Datagram->GetData();
						Data[BytesRead] = '\0';
						recvMessage = FString(UTF8_TO_TCHAR(Data));

						/*if (GEngine)
							GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, FString::Printf(TEXT("HTMLMenu: 25: %s"), *recvMessage))*/;

							//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket get Handshake Data: %s"), *recvMessage);

						TArray<FString> dataLines;
						recvMessage.ParseIntoArray(dataLines, TEXT("\r\n"), true);
						for (int i = 0; i < dataLines.Num(); i++) {
							if (dataLines[i].StartsWith("Sec-WebSocket-Key")) {
								FString clientKey = dataLines[i].Replace(TEXT("Sec-WebSocket-Key: "), TEXT(""));
								//clientKey = recvMessage.Replace(TEXT("\r"), TEXT(""));
								//clientKey = recvMessage.Replace(TEXT("\n"), TEXT(""));
								FString handshake = generateHandshakeData(clientKey);
								//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket send Handshake Data: %s"), *handshake);

								FTCHARToUTF8 Convert(*handshake);
								int32 sent = 0;
								clientSocket->Send((uint8*)((ANSICHAR*)Convert.Get()), Convert.Length(), sent);
								needHandshake = false;

								/*if (GEngine)
									GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, FString::Printf(TEXT("HTMLMenu: 22: %s"), *handshake));*/
								break;
							}
						}
						continue;
					}
					//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Data 1"));

					if (Datagram->Num() >= 6) {
						//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Data 2"));
						TArray<uint8> data;
						TArray<uint8> key;
						uint64 firstDataByteIndex = 0;
						data.Append(Datagram->GetData(), Datagram->Num());
						uint64	websocketFrameDataSize = 0;

						//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Dataframe Size: %i"), data.Num());
						if (data[0] == 129) {
							//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Data 3"));
							uint8 tmp = data[1] - 128;
							if (tmp >= 0 && tmp <= 125) {
								websocketFrameDataSize = tmp;
								key.Add(data[2]);
								key.Add(data[3]);
								key.Add(data[4]);
								key.Add(data[5]);
								firstDataByteIndex = 6;
							}
							else {
								if (tmp == 126 && Datagram->Num() >= 8) {
									//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Data 4"));
									uint16 tmp16 = data[2] << 8 | data[3] << 0;
									websocketFrameDataSize = tmp16;
									key.Add(data[4]);
									key.Add(data[5]);
									key.Add(data[6]);
									key.Add(data[7]);
									firstDataByteIndex = 8;
								}
								if (tmp == 127 && Datagram->Num() >= 14) {
									//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Data 5"));
									// error C4293: '<<': shift count negative or too big, undefined behavior
									//websocketFrameDataSize = data[2] << 56 | data[3] << 48 | data[4] << 40 | data[5] << 32 | data[6] << 24 | data[7] << 16 | data[8] << 8 | data[9] << 0;
									//key.Add(data[10]);
									//key.Add(data[11]);
									//key.Add(data[12]);
									//key.Add(data[13]);
									//firstDataByteIndex = 14;
								}

							}
						}
						if (websocketFrameDataSize > 0 && key.Num() == 4 && firstDataByteIndex > 0) {
							//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Data 6"));
							//decode data to string
							TArray<uint8> decoded;
							int j = 0;
							for (int i = firstDataByteIndex; i < data.Num(); i++) {
								uint8 b = key[j];
								decoded.Add(data[i] ^ b);
								j++;
								if (j > 3)
									j = 0;
							}
							char* Data = (char*)decoded.GetData();
							Data[decoded.Num()] = '\0';
							FString recvMessage = FString(UTF8_TO_TCHAR(Data));
							//UE_LOG(LogTemp, Display, TEXT("HTMLMenu Websocket Data: %s"),*recvMessage);
							/*if (GEngine)
								GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, FString::Printf(TEXT("HTMLMenu: 23: %s"), *recvMessage));*/
							if (mainlib != nullptr)
								mainlib->handleWebsocketData(recvMessage);
							decoded.Empty();
						}
						else {
							UE_LOG(LogTemp, Warning, TEXT("HTMLMenu Websocket Data cannot be processed(1)."));
						}


						data.Empty();
						key.Empty();
						firstDataByteIndex = 0;
						Datagram->Empty();
						websocketFrameDataSize = 0;
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("HTMLMenu Websocket Data cannot be processed(2)."));
					}
				}
			}
		}

		//UE_LOG(LogTemp, Display, TEXT("Websocket Disconnect"));

		run = false;

		//clean up socket
		if (clientSocket != nullptr) {
#if PLATFORM_IOS
			clientSocket->Close();
#endif
			clientSocket = nullptr;
		}
		thread = nullptr;

		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("END B"));*/
		return 0;
	}

public:
	void closeClientConnection() {
		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("closeClientConnection"));*/
		if (run) {
			run = false;
#if PLATFORM_IOS
			if (clientSocket != nullptr) {
				//send websocket close handshake
				TArray<uint8> closeCommand;
				closeCommand.Add(0xFF);
				closeCommand.Add(0x00);
				int32 sent = 0;
				clientSocket->Send(closeCommand.GetData(), closeCommand.Num(), sent);

				clientSocket->Close();
			}
#endif
#if PLATFORM_ANDROID
			if (mainlib != nullptr)
				mainlib->callJavascript("closeWebsocket();");
#endif
		}
	}

	bool isRun() {
		return run;
	}


private:
	FSocket* clientSocket = nullptr;
	FRunnableThread* thread = nullptr;

	bool	needHandshake = true;
	bool	run = true;
	UHTMLMenuMainBPLibrary* mainlib = nullptr;

	FString generateHandshakeData(FString clientKey) {
		FString handshakeData = "HTTP/1.1 101 \r\nUpgrade: websocket\r\nConnection: upgrade\r\nSec-WebSocket-Accept: ";
		clientKey += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
		FSHAHash Hash;
		FTCHARToUTF8 Convert(*clientKey);
		FSHA1::HashBuffer((uint8*)((ANSICHAR*)Convert.Get()), Convert.Length(), Hash.Hash);
		TArray<uint8> sha1EncodedBytes;
		sha1EncodedBytes.Append(Hash.Hash, 20);
		handshakeData += FBase64::Encode(sha1EncodedBytes) + "\r\n\r\n";
		return handshakeData;


		/*	FTCHARToUTF8 Convert(*clientKey);
			FSHA1::HashBuffer((uint8*)((ANSICHAR*)Convert.Get()), Convert.Length(), outbuffer.GetData());*/
	}
};

/*SERVER start and create client sockets asynchronous Thread*/
class FHtmlMenuWebsocketServerThread : public FRunnable {

public:

	FHtmlMenuWebsocketServerThread(UHTMLMenuMainBPLibrary* mainlibP) :
		mainlib(mainlibP) {
		FString threadName = "FHtmlMenuWebsocketServerThread_" + FGuid::NewGuid().ToString();
		thread = FRunnableThread::Create(this, *threadName, 0, EThreadPriority::TPri_Normal);
	}

	virtual uint32 Run() override {
		FIPv4Endpoint boundEndpoint;

		while (socketSubSystem != nullptr && websocketPortMin <= websocketPortMax) {

			if (serverStarted == false) {

				if (listenerSocket != nullptr) {
					listenerSocket->Close();
					listenerSocket = nullptr;
					FPlatformProcess::Sleep(0.2);
				}

				boundEndpoint = FIPv4Endpoint(FIPv4Address(127, 0, 0, 1), websocketPortMin);
				listenerSocket = socketSubSystem->CreateSocket(NAME_Stream, *FString("UHTMLMenuWebsocketServer"), boundEndpoint.ToInternetAddrIPV4()->GetProtocolType());

				if (listenerSocket != nullptr) {

					if (!listenerSocket->Bind(*boundEndpoint.ToInternetAddrIPV4())) {
						if (listenerSocket != nullptr) {
							listenerSocket->Close();
							if (socketSubSystem != nullptr)
								socketSubSystem->DestroySocket(listenerSocket);
							listenerSocket = nullptr;
							websocketPortMin++;
							FPlatformProcess::Sleep(0.2);
							continue;
						}
					}


					if (!listenerSocket->Listen(8)) {
						if (listenerSocket != nullptr) {
							listenerSocket->Close();
							if (socketSubSystem != nullptr)
								socketSubSystem->DestroySocket(listenerSocket);
							listenerSocket = nullptr;
						}
					}
				}

				if (listenerSocket == nullptr) {
					websocketPortMin++;
					FPlatformProcess::Sleep(0.2);
					continue;
				}

				/*if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, TEXT("Server Started on:") + FString::FromInt(websocketPortMin));*/

				serverStarted = true;
			}

			if (websocketClientThread != nullptr) {
				/*if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, TEXT("Close client"));*/
				websocketClientThread->closeClientConnection();
				websocketClientThread = nullptr;
			}

			/*if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, TEXT("After Close client"))*/;

			mainlib->callJavascript("openWebsocket(" + FString::FromInt(websocketPortMin) + ");");
			int32 connectionAttempts = 20;
			while (listenerSocket != nullptr && connected == false) {
				connectionAttempts--;
				bool pending;
				listenerSocket->WaitForPendingConnection(pending, FTimespan::FromSeconds(1));
				//listenerSocket->HasPendingConnection(pending);
				if (pending) {
					TSharedRef<FInternetAddr> remoteAddress = socketSubSystem->CreateInternetAddr();
					FSocket* clientSocket = listenerSocket->Accept(*remoteAddress, FGuid::NewGuid().ToString());
					/*if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("New websocketClient Thread"));*/
					websocketClientThread = new FHtmlMenuWebsocketClientThread(clientSocket, mainlib);
					connected = true;
					/*if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("Client connected"));*/
					break;
				}
				else {
					mainlib->callJavascript("openWebsocket(" + FString::FromInt(websocketPortMin) + ");");
				}
				if (connectionAttempts < 0) {
					break;
				}
			}
	


			pauseThread(true);
			//workaround. suspend do not work on all platforms. lets sleep
			while (paused) {
				FPlatformProcess::Sleep(0.01);
			}

		}

		return 0;
	}

public:

	void pauseThread(bool pause) {
		paused = pause;
		thread->Suspend(pause);
	}

	void allowNewConnection() {
		if (listenerSocket != nullptr) {
		/*	if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, FString("END A ") + FString::FromInt(listenerSocket->GetConnectionState())+" "+ FString::FromInt(socketSubSystem->GetLastErrorCode()));*/
			if (listenerSocket->GetConnectionState() != 0) {
				//UE_LOG(LogTemp, Warning, TEXT("allowNewConnection: %i %i "), listenerSocket->GetConnectionState(), socketSubSystem->GetLastErrorCode());
				serverStarted = false;
			}
			else {
				if (websocketClientThread != nullptr) {
					if (websocketClientThread->isRun() == false) {
						serverStarted = false;
					}
				}
			}
		}
		else {
			serverStarted = false;
		}
		connected = false;
		pauseThread(false);
	}

	void test() {
		listenerSocket->Close();
		if (websocketClientThread != nullptr) {
			websocketClientThread->closeClientConnection();
		}
	}


private:
	FRunnableThread* thread = nullptr;
	FSocket* listenerSocket = nullptr;
	bool connected = false;
	bool serverStarted = false;
	bool paused = false;
	UHTMLMenuMainBPLibrary* mainlib = nullptr;

	TArray<int32> ipArray;
	int32 websocketPortMin = 49800;
	int32 websocketPortMax = 50000;
	
	FHtmlMenuWebsocketClientThread* websocketClientThread = nullptr;
	ISocketSubsystem* socketSubSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
};
