// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerSDF.h"
#include "ShowdownBPFL.h"

void AControllerSDF::UpdateAvailableActions() {
	if (bStunned) {
		availableActions.CanFake = false;
		availableActions.CanBreakAway = false;
		availableActions.CanShoot = false;
		availableActions.CanBlock = false;
		availableActions.CanPysche = false;
		availableActions.CanSteal = false;
	}
	else if (hasPossession()) {
		availableActions.CanFake = true;
		availableActions.CanBreakAway = true;
		availableActions.CanShoot = true;
		availableActions.CanBlock = false;
		availableActions.CanPysche = false;
		availableActions.CanSteal = false;
	}
	else {
		availableActions.CanFake = false;
		availableActions.CanBreakAway = false;
		availableActions.CanShoot = false;
		availableActions.CanBlock = true;
		availableActions.CanPysche = true;
		availableActions.CanSteal = true;
	}
}


float AControllerSDF::GetStatForAction(E_PlayerActions action) {
	float stat = 0.0f;

	switch (action) {

	case E_PlayerActions::Shoot:
		stat = this->baseStats.Accuracy + this->gearStats.Accuracy;
		break;


	case E_PlayerActions::Block:
		stat = this->baseStats.Defense + this->gearStats.Defense;
		break;

	case E_PlayerActions::BreakAway:
		stat = this->baseStats.Athleticism + this->gearStats.Athleticism;
		break;

	case E_PlayerActions::Fake:
		stat = this->baseStats.Vision + this->gearStats.Vision;
		break;

	case E_PlayerActions::Pysche:
		stat = this->baseStats.Vision + this->gearStats.Vision;
		break;

	case E_PlayerActions::Steal:
		stat = this->baseStats.Handles + this->gearStats.Handles;
		break;

	default:
		break;
	}

	return stat;
}

//TODO: figure out how to 'static' this
bool AControllerSDF::hasPossession() {
	if (gameStateRef) {
		return (this->Team == gameStateRef->possession);
	}
	else {
		return false;
	}
}

void AControllerSDF::SetGameStateRef() {
	UWorld* world = GetWorld();
	gameStateRef = nullptr;
	if (world)
	{
		gameStateRef = Cast<AGameStateSDF>(world->GetGameState());
	}
}

void AControllerSDF::TakeAction(E_PlayerActions actionToTake) {
	if (gameStateRef) {
		FShowdownPlayerActionData data;

		data.ActionTimeReamining = gameStateRef->actionTimerCount / 10;
		data.Action = actionToTake;
		data.ActionStat = this->GetStatForAction(actionToTake);
		data.Team = Team;

		gameStateRef->OnActionAttempt(data);
	}
}


// #region SHOWDOWN INTERFACE

void AControllerSDF::OnActionSucess_Implementation(E_PlayerActions Action) {
	return;
}

void AControllerSDF::OnActionFail_Implementation(bool bTimedOut, E_PlayerActions Action) {
	return;
}

void AControllerSDF::OnShotClockEnd_Implementation(bool bTimedOut) {
	return;
}

void AControllerSDF::OnGameClockEnd_Implementation() {
	return;
}


void AControllerSDF::OnDriveStart_Implementation(E_Team currentPossession) {
	bStunned = false;
	return;
}

void AControllerSDF::OnGameplayEvent_Implementation(E_GameEvent Event) {

	switch (Event) {

	case(E_GameEvent::AwaitingAction):
		this->UpdateAvailableActions();
		break;

	default:
		break;
	}

	return;
}


void AControllerSDF::OnStunEffect_Implementation(bool bDisableEffect) {
	bStunned = !bDisableEffect;
	UpdateAvailableActions();
	return;
}

// #endregion SHOWDOWN INTERFACE
