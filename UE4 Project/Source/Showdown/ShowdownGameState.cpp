// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowdownGameState.h"

// Setting up custom log category for class
DEFINE_LOG_CATEGORY(CUSTOM_GameState);
// ex : UE_LOG(CUSTOM_<class>, <type>, TEXT("<message>"));

void AShowdownGameState::StartShotClock() {

	GetWorldTimerManager().SetTimer(shotClockTimerHandle, this, &AShowdownGameState::AdvanceShotClock, 5.0f, true);

	return;
}

void AShowdownGameState::AdvanceShotClock() {

	//decrement the timer and update the display
	--showClockCount;

	//if the timer is done clear and complete the timer with the flag set
	if (showClockCount <= 0){
		EndShotClock(true);
	}

}

void AShowdownGameState::EndShotClock(bool timedOut) {

	//clear timer
	GetWorldTimerManager().ClearTimer(shotClockTimerHandle);

}

void AShowdownGameState::StartGameClock() {

	GetWorldTimerManager().SetTimer(gameClockTimerHandle, this, &AShowdownGameState::AdvanceGameClock, 5.0f, true);
	
	return;
}

void AShowdownGameState::AdvanceGameClock() {

	//decrement the timer and update the display
	--gameClockCount;

	//if the timer is done clear and complete the timer with the flag set
	if (gameClockCount <= 0){
		EndGameClock(true);
	}

}

void AShowdownGameState::EndGameClock(bool timedOut) {

	//clear timer
	GetWorldTimerManager().ClearTimer(gameClockTimerHandle);

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