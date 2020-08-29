// Copyright 2018-2020 David Romanski (Socke). All Rights Reserved.

#include "HTMLMenuMainBPLibrary.h"


UHTMLMenuMainBPLibrary* UHTMLMenuMainBPLibrary::HTMLMenuMainBPLibrary;

UHTMLMenuMainBPLibrary::UHTMLMenuMainBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer){
	HTMLMenuMainBPLibrary = this;
}

UHTMLMenuMainBPLibrary* UHTMLMenuMainBPLibrary::getHTMLMenuMainBPLibrary(){
	return HTMLMenuMainBPLibrary;
}

void UHTMLMenuMainBPLibrary::initWebsocketServer(UHTMLMenu* menuP){
	menu = menuP;

	if (websocketServerThread == nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("HTMLMenu initWebserver 1"));
		websocketServerThread = new FHtmlMenuWebsocketServerThread(this);
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, TEXT("appReactivtedDelegate 1"));
	}
	else {
		if (isInConnectionProcess)
			return;
		isInConnectionProcess = true;
		//UE_LOG(LogTemp, Warning, TEXT("HTMLMenu initWebserver 2"));
		websocketServerThread->allowNewConnection();
		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, TEXT("appReactivtedDelegate 2"));*/
	}

}

void UHTMLMenuMainBPLibrary::callJavascript(FString javascript){
	/*AsyncTask(ENamedThreads::GameThread, [javascript]() {
		UHTMLMenuMainBPLibrary::getHTMLMenuMainBPLibrary()->getMenu()->ExecuteJavascript(javascript);
	});*/

	if (menu->IsValidLowLevelFast()) {
		menu->ExecuteJavascript(javascript);
	}
	
}

void UHTMLMenuMainBPLibrary::handleWebsocketData(FString& data){
	menu->handleWebsocketData(data);
}

UHTMLMenu* UHTMLMenuMainBPLibrary::getMenu() {
	return menu;
}

void UHTMLMenuMainBPLibrary::setInConnectionProcess(bool connectionp)
{
	isInConnectionProcess = connectionp;
}

//void UHTMLMenuMainBPLibrary::testAbc()
//{
//	UHTMLMenuMainBPLibrary::getHTMLMenuMainBPLibrary()->testaaa();
//}
//
//void UHTMLMenuMainBPLibrary::testaaa()
//{
//	websocketServerThread->test();
//}

