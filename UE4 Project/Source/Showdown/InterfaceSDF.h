// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShowdownBPFL.h"
#include "InterfaceSDF.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceSDF : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOWDOWN_API IInterfaceSDF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * OnActionSucess fires when a action is successful
	 * @param Action the action the player took
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnActionSucess(E_PlayerActions Action);

	/**
	 * OnActionFail fires when a action fails or the timer has ran out
	 * @param bTimedOut did the timer run out?
	 * @param Action the action the player took
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnActionFail(bool bTimedOut, E_PlayerActions Action);

	/**
	 * OnActionAttempt fires when an action  is attempted.
	 * @param Action the action that the player took
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnActionAttempt(FShowdownPlayerActionData Action);

	/**
	 * OnDriveStart fires when a 'round' of play begins
	 * @param currentPossession which player should current have the ball
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnDriveStart(E_Team currentPossession);

	/**
	 * OnShotClockEnd fires when the shot clock runs out
	 * @param bTimedOut did the timer run out?
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnShotClockEnd(bool bTimedOut);

	/**
	 * OnGameClockEnd fires when the game clock runs out
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnGameClockEnd();

	/**
	 * OnGameEvent fires when a game event happens
	 * @param Event the event that happened
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnGameplayEvent(E_GameEvent Event);

	/**
	 * OnStunEffect fires when the possessing player is stunned
	 * @param bDisableEffect the stun effect
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void OnStunEffect(bool bDisableEffect);
};
