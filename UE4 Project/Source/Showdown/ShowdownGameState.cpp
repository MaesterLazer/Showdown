// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowdownGameState.h"

// Setting up custom log category for class
DEFINE_LOG_CATEGORY(CUSTOM_GameState);
// ex : UE_LOG(CUSTOM_<class>, <type>, TEXT("<message>"));

void AShowdownGameState::BeginPlay() {
	GameMode = (AShowdownGameMode *)GetWorld()->GetAuthGameMode();

	if (GameMode != nullptr) {
		UE_LOG(CUSTOM_GameState, Warning, TEXT("gamemode ref set via C++"));
	}
}

void AShowdownGameState::StartShotClock() {

	shotClockCount = this->GameMode->shotClockTimeLimit;
	UE_LOG(CUSTOM_GameState, Warning, TEXT("set shot clock value to %f"), shotClockCount);

	GetWorldTimerManager().SetTimer(
		shotClockTimerHandle, 
		this, 
		&AShowdownGameState::AdvanceShotClock, 
		1.0f, 
		true
	);

	return;
}

void AShowdownGameState::AdvanceShotClock() {

	//decrement the timer and update the display
	--shotClockCount;

	//UE_LOG(CUSTOM_GameState, Warning, TEXT("advance shot clock value to %f"), shotClockCount);

	//if the timer is done clear and complete the timer with the flag set
	if (shotClockCount <= 0){
		EndShotClock(true);
	}

}

void AShowdownGameState::EndShotClock(bool timedOut) {

	//clear timer
	GetWorldTimerManager().ClearTimer(shotClockTimerHandle);
	
	if (timedOut) {
		EventOnShotClockEnd();
	}

}

void AShowdownGameState::StartGameClock() {

	gameClockCount = this->GameMode->gameTimeLimit;
	UE_LOG(CUSTOM_GameState, Warning, TEXT("set game clock value to %f"), gameClockCount);

	GetWorldTimerManager().SetTimer(
		gameClockTimerHandle, 
		this, 
		&AShowdownGameState::AdvanceGameClock, 
		1.0f, 
		true
	);
	
	return;
}

void AShowdownGameState::AdvanceGameClock() {

	//decrement the timer and update the display
	--gameClockCount;

	//UE_LOG(CUSTOM_GameState, Warning, TEXT("advance game clock value to %f"), gameClockCount);


	//if the timer is done clear and complete the timer with the flag set
	if (gameClockCount <= 0){
		EndGameClock(true);
	}

}

void AShowdownGameState::EndGameClock(bool timedOut) {

	//clear timer
	GetWorldTimerManager().ClearTimer(gameClockTimerHandle);

	if (timedOut) {
		EventOnGameClockEnd();
	}

}


void AShowdownGameState::RegisterGameObjects(FGameplayObjects newGameObjects){
	this->gameObjects = newGameObjects;

	UE_LOG(CUSTOM_GameState, Warning, TEXT("gameplay refs set to GameState"));
	return;
}

void AShowdownGameState::EventScore_Implementation(){
	return;
}

void AShowdownGameState::EventShotAttempt_Implementation(){
	return;
}

void AShowdownGameState::EventBallStateChange_Implementation(E_BallState NewState) {
	//TODO: Set ball state here
	return;
}

void AShowdownGameState::EventOnGameClockEnd_Implementation() {
	UE_LOG(CUSTOM_GameState, Warning, TEXT("game clock end fire"));
	return;
}

void AShowdownGameState::EventOnShotClockEnd_Implementation() {
	UE_LOG(CUSTOM_GameState, Warning, TEXT("shot clock end fire"));
	return;
}

void AShowdownGameState::EventOnGameClockStart_Implementation() {
	StartGameClock();
	UE_LOG(CUSTOM_GameState, Warning, TEXT("game clock start fire"));
	return;
}

void AShowdownGameState::EventOnShotClockStart_Implementation() {
	StartShotClock();
	UE_LOG(CUSTOM_GameState, Warning, TEXT("shot clock start fire"));
	return;
}