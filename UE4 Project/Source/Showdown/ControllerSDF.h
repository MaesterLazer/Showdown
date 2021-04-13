// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShowdownBPFL.h"
#include "InterfaceSDF.h"
#include "GameStateSDF.h"
#include "GameFramework/PlayerController.h"
#include "ControllerSDF.generated.h"

/**
 * 
 */
UCLASS()
class SHOWDOWN_API AControllerSDF : public APlayerController
{
	GENERATED_BODY()

private:

	void UpdateAvailableActions();

	float GetStatForAction(E_PlayerActions action);

public:

	UFUNCTION(BlueprintCallable, Category = "Showdown Framework | Player")
		void SetGameStateRef();

	UFUNCTION(BlueprintCallable, Category = "Showdown Framework | Player")
		void TakeAction(E_PlayerActions actionToTake);


	UFUNCTION(BlueprintCallable, Category = "Showdown Framework | Player")
		bool hasPossession();

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Player")
		FShowdownPlayerStats baseStats;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Player")
		FShowdownPlayerStats gearStats;

	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | Player")
		FShowdownPlayerActions availableActions;

	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | Player")
		int32 xp;

	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | Player")
		AGameStateSDF *gameStateRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Showdown Framework | Player")
		E_Team Team;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Showdown Framework | Player")
		bool bStunned;


	// #region SHOWDOWN INTERFACE

				/**
				 * OnActionSucess fires when a action is successful
				 * @param Action the action the player took
				*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnActionSucess(E_PlayerActions Action);
	virtual void OnActionSucess_Implementation(E_PlayerActions Action);

	/**
	 * OnActionFail fires when a action fails or the timer has ran out
	 * @param bTimedOut did the timer run out?
	 * @param Action the action the player took
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnActionFail(bool bTimedOut, E_PlayerActions Action);
	virtual void OnActionFail_Implementation(bool bTimedOut, E_PlayerActions Action);


	/**
	 * OnDriveStart fires when a 'round' of play begins
	 * @param currentPossession which player should current have the ball
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnDriveStart(E_Team currentPossession);
	virtual void OnDriveStart_Implementation(E_Team currentPossession);

	/**
	 * OnShotClockEnd fires when the shot clock runs out
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnShotClockEnd(bool bTimedOut);
	virtual void OnShotClockEnd_Implementation(bool bTimedOut);

	/**
	 * OnGameClockEnd fires when the game clock runs out
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnGameClockEnd();
	virtual void OnGameClockEnd_Implementation();

	/**
	 * OnGameEvent fires when a gameplay event happens
	 * @param Event the event that happened
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnGameplayEvent(E_GameEvent Event);
	virtual void OnGameplayEvent_Implementation(E_GameEvent Event);

	/**
	* OnStunEffect fires when the possessing player is stunned
	* @param bDisableEffect the stun effect
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnStunEffect(bool bDisableEffect);
	virtual void OnStunEffect_Implementation(bool bDisableEffect);

	// #endregion SHOWDOWN INTERFACE


	
};
