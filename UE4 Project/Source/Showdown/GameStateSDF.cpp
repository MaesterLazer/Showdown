// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateSDF.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"


// Setting up custom log category for class
DEFINE_LOG_CATEGORY(CUSTOM_GameStateSDF);
// ex : UE_LOG(CUSTOM_<class>, <type>, TEXT("<message>"));


void AGameStateSDF::BeginPlay() {
	GameMode = (AGameModeSDF *)GetWorld()->GetAuthGameMode();
	scoreAway = 0;
	scoreHome = 0;
	possession = E_Team::Home;
	homePlayerTakenAction = false;
	awayPlayerTakenAction = false;

	if (GameMode != nullptr) {
		UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("gamemode ref set via C++"));
	}
}

void AGameStateSDF::RegisterGameObjects(FGameplayObjects objs) {
	this->gameObjects = objs;
	this->OnGameplayEvent(E_GameEvent::Init);
	return;
}


void AGameStateSDF::OnStunPossessingPlayer_Implementation(bool bDisableStun) {
	if (bDisableStun == false) {
		StartStunClock();
	}
	else {
		StartActionTimer();
	}
	return;
}

void AGameStateSDF::StartStunClock() {

	stunTimeCount = this->GameMode->stunBaseTimeLimit;
	UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("set stun clock value to %f"), stunTimeCount);

	GetWorldTimerManager().SetTimer(
		stunTimerHandle,
		this,
		&AGameStateSDF::AdvanceStunClock,
		1.0f,
		true
	);

	return;
}

void AGameStateSDF::AdvanceStunClock() {

	//decrement the timer and update the display
	--stunTimeCount;

	//UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("advance shot clock value to %f"), shotClockCount);

	//if the timer is done clear and complete the timer with the flag set
	if (stunTimeCount <= 0) {
		EndStunClock();
	}
	else {
		//this->OnShotClockAdvance(shotClockCount);
	}

	return;
}

void AGameStateSDF::EndStunClock() {

	//clear timers
	GetWorldTimerManager().ClearTimer(stunTimerHandle);

	OnStunPossessingPlayer(true);

	return;
}

void AGameStateSDF::StartShotClock() {

	shotClockCount = this->GameMode->shotClockTimeLimit;
	UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("set shot clock value to %f"), shotClockCount);

	GetWorldTimerManager().SetTimer(
		shotClockTimerHandle,
		this,
		&AGameStateSDF::AdvanceShotClock,
		1.0f,
		true
	);

	return;
}

void AGameStateSDF::AdvanceShotClock() {

	//decrement the timer and update the display
	--shotClockCount;

	//UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("advance shot clock value to %f"), shotClockCount);

	//if the timer is done clear and complete the timer with the flag set
	if (shotClockCount <= 0) {
		EndShotClock(true);
	}
	else {
		//this->OnShotClockAdvance(shotClockCount);
	}

	return;
}

void AGameStateSDF::EndShotClock(bool timedOut) {

	//clear timers
	GetWorldTimerManager().ClearTimer(shotClockTimerHandle);

	if (timedOut) {
		OnShotClockEnd(true);
	}
	else {
		EndActionTimer(false);
	}

	return;
}

void AGameStateSDF::StartGameClock() {

	gameClockCount = this->GameMode->gameTimeLimit;
	UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("set game clock value to %f"), gameClockCount);

	GetWorldTimerManager().SetTimer(
		gameClockTimerHandle,
		this,
		&AGameStateSDF::AdvanceGameClock,
		1.0f,
		true
	);

	return;
}

void AGameStateSDF::AdvanceGameClock() {

	//decrement the timer and update the display
	--gameClockCount;

	//UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("advance game clock value to %f"), gameClockCount);


	//if the timer is done clear and complete the timer with the flag set
	if (gameClockCount <= 0) {
		EndGameClock();
	}
	else {
		//this->OnGameClockAdvance(gameClockCount);
	}

	return;
}

void AGameStateSDF::EndGameClock() {

	//clear timer
	GetWorldTimerManager().ClearTimer(gameClockTimerHandle);

	OnGameClockEnd();

	return;
}

void AGameStateSDF::StartActionTimer() {

	actionTimerCount = this->GameMode->actionTimerLimit;
	UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("set actoin timer value to %f"), actionTimerCount);

	GetWorldTimerManager().SetTimer(
		actionTimerHandle,
		this,
		&AGameStateSDF::AdvanceActionTimer,
		1.0f,
		true
	);

	return;
}

void AGameStateSDF::AdvanceActionTimer() {

	//decrement the timer and update the display
	--actionTimerCount;

	//UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("advance game clock value to %f"), gameClockCount);


	//if the timer is done clear and complete the timer with the flag set
	if (actionTimerCount <= 0) {
		EndActionTimer(true);
	}

	return;
}

void AGameStateSDF::EndActionTimer(bool timedOut) {

	//clear timer
	GetWorldTimerManager().ClearTimer(actionTimerHandle);

	if (timedOut) {
		// TODO: call timeout function
		UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("action timer timedout"));
		this->OnGameplayEvent(E_GameEvent::ActionTimedOut);
	}

	return;
}

void AGameStateSDF::GetPlayerActionResults() {

	//get base for success
	float failureThershold = FMath::RandRange(0.0f, 1.0f);
	float savingThershold = 0;
	E_PlayerActions actionTaken = E_PlayerActions::None;

	//get data for fail throw and saving throw
	switch (possession) {
	case E_Team::Home:
		savingThershold = homePlayerActionData.ActionStat + homePlayerActionData.ActionTimeReamining;
		failureThershold = awayPlayerActionData.ActionStat + failureThershold;
		actionTaken = homePlayerActionData.Action;
		break;

	case E_Team::Away:
		savingThershold = awayPlayerActionData.ActionStat + awayPlayerActionData.ActionTimeReamining;
		failureThershold = homePlayerActionData.ActionStat + failureThershold;
		actionTaken = awayPlayerActionData.Action;
		break;

	default:
		break;
	}

	if (actionTaken == E_PlayerActions::Shoot) {
		float mod = GetDistanceToBasketModifier();
		failureThershold += mod;
	}

	bool bDidSave = savingThershold >= failureThershold;

	UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("player action results | did save? %s | saving throw: %f failure throw: %f"), (bDidSave ? TEXT("true") : TEXT("false")), savingThershold, failureThershold);

	if (bDidSave) {
		this->OnActionSucess(actionTaken);
	}
	else {
		this->OnActionFail(false, actionTaken);
	}

	//Reset action state
	homePlayerTakenAction = false;
	awayPlayerTakenAction = false;

	return;
}


void AGameStateSDF::UpdateScore() {

	switch (possession) {
	case E_Team::Home:
		scoreHome += 1;
		break;
	case E_Team::Away:
		scoreAway += 1;
		break;
	case E_Team::Free:
		break;
	default:
		break;
	}
}


float AGameStateSDF::GetDistanceToBasketModifier() {

	float value = 0.0f;

	FVector playerPos = FVector(0, 0, 0);

	// get position based on who has the ball
	switch (possession) {
	default:
		break;
	case E_Team::Home:
		playerPos = gameObjects.HomePlayer->GetPawn()->GetActorLocation();
		break;
	case E_Team::Away:
		playerPos = gameObjects.AwayPlayer->GetActorLocation();
		break;
	case E_Team::Free:
		break;
	}

	FVector hoopPos = gameObjects.Hoop->GetActorLocation();

	float distance = FVector::DistXY(playerPos, hoopPos);

	value = distance * GameMode->distanceToGoalMultiplier;

	UE_LOG(CUSTOM_GameStateSDF, Warning, TEXT("distance to basket modifier results | distnace : %f  value: %f"), distance, value);

	return value;

}

// #region SHOWDOWN INTERFACE

void AGameStateSDF::OnActionSucess_Implementation(E_PlayerActions Action) {
	this->OnGameplayEvent(E_GameEvent::ActionSuccess);
	return;
}

void AGameStateSDF::OnActionFail_Implementation(bool bTimedOut, E_PlayerActions Action) {
	this->OnGameplayEvent(E_GameEvent::ActionFailed);
	return;
}

void AGameStateSDF::OnShotClockEnd_Implementation(bool bTimedOut) {
	if (bTimedOut) {
		this->OnGameplayEvent(E_GameEvent::ShotClockTimeout);
	}
	return;
}

void AGameStateSDF::OnGameClockEnd_Implementation() {
	this->OnGameplayEvent(E_GameEvent::GameClockTimeout);
	return;
}

void AGameStateSDF::OnActionAttempt_Implementation(FShowdownPlayerActionData Action) {

	switch (Action.Team) {
	case(E_Team::Home):
		homePlayerActionData = Action;
		homePlayerTakenAction = true;
		break;

	case(E_Team::Away):
		awayPlayerActionData = Action;
		awayPlayerTakenAction = true;
		break;

	default:
		break;
	}

	if (homePlayerTakenAction == true && awayPlayerTakenAction == true) {
		this->GetPlayerActionResults();
		this->EndActionTimer(false);
	}

	return;
}

void AGameStateSDF::OnDriveStart_Implementation(E_Team currentPossession) {
	StartShotClock();
	return;
}

void AGameStateSDF::OnGameplayEvent_Implementation(E_GameEvent Event) {

	switch (Event)
	{
	case E_GameEvent::BasketMade:
		UpdateScore();
		break;
	case E_GameEvent::ReboundOpprotunity:
		break;
	case E_GameEvent::BallStolen:
		break;
	case E_GameEvent::ShotClockTimeout:
		break;
	case E_GameEvent::GameClockTimeout:
		break;
	case E_GameEvent::DriveStart:
		OnDriveStart(possession);
		break;
	case E_GameEvent::AwaitingAction:
		StartActionTimer();
		break;
	case E_GameEvent::ActionFailed:
		break;
	case E_GameEvent::ActionTimedOut:
		break;
	case E_GameEvent::ActionSuccess:
		break;
	case E_GameEvent::GameStart:
		StartGameClock();
		break;
	case E_GameEvent::Init:
		break;
	default:
		break;
	case E_GameEvent::ChangePossession:
		switch (possession) {
		case E_Team::Home:
			possession = E_Team::Away;
			break;
		case E_Team::Away:
			possession = E_Team::Home;
			break;
		case E_Team::Free:
			break;
		default:
			break;
		}
		break;
	}
	return;
}


// #endregion SHOWDOWN INTERFACE
