// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShowdownBPFL.h"
#include "UObject/Interface.h"
#include "ShowdownInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UShowdownInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *  Main interface interacting with GameState and game objects 
 */
class SHOWDOWN_API IShowdownInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	* EventBallStateChange fires when there is a change in the Ball object state. 
	*
	* @param NewState new state of the ball
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventBallStateChange(E_BallState NewState);

	/**
	* EventPossessionChange fires when there is a change of possession.
	*
	* @param NewState new state of possession
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventPossessionChange(E_CurrentPossession NewState);

	/**
	* EventScore fires when a shot is made.
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventScore();

	/**
	* EventShotAttempt fires when a shot at the basket is attempted.
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventShotAttempt();

	/**
	* EventShotAttempt fires when a player attempts to steal the ball.
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventStealAttempt();

	/**
	* EventOnShotClockEnd fires when the shock clock times out
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventOnShotClockEnd();

	/**
	* EventOnGameClockEnd fires when the game clock times out
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventOnGameClockEnd();

	/**
	* EventOnShotClockStart fires when the shock clock starts
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventOnShotClockStart();

	/**
	* EventOnGameClockStart fires when the game clock starts
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventOnGameClockStart();

	/**
	* EventOnRegisterGameObjects fires when the gamestate gets the gameplay refs
	*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Interface")
		void EventOnRegisterGameObjects(FGameplayObjects newGameObjects);


};
