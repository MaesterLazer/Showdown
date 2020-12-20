// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShowdownInterface.h"
#include "ShowdownGameMode.h"
#include "ShowdownGameState.generated.h"


// Setting up custom log category for class
DECLARE_LOG_CATEGORY_EXTERN(CUSTOM_GameState, Log, All);

/**
 * GameStateBase subclass for the Showdown Game.
 */
UCLASS()
class SHOWDOWN_API AShowdownGameState : public AGameStateBase, public IShowdownInterface
{
	GENERATED_BODY()
	private:

		/**
		 *  Function to start Shot Clock
		 */
		void StartShotClock();

		/**
		 *  Function to advance Shot Clock and increment counter for ui
		 */
		void AdvanceShotClock();

		/**
		 *  Function to end Shot Clock
		 *
		 *	@param timedOut did the clock time out? 
		 */
		void EndShotClock(bool timedOut);

		/**
		 *  Function to start Game Clock
		 */
		void StartGameClock();

		/**
		 *  Function to advance Game Clock and increment counter for ui
		 */
		void AdvanceGameClock();

		/**
		 *  Function to end Game Clock
		 *
		 *	@param timedOut did the clock time out?
		 */
		void EndGameClock(bool timedOut);

	public:

		/**
		 *  BeginPlay override
		 */
		UFUNCTION(BlueprintCallable)
			virtual void BeginPlay() override;

		/**
		 *  Pointer for Showdown GameMode
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | GameplayElements")
			AShowdownGameMode * GameMode;

		/**
		 *  Pointer for game objects
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | GameplayElements")
			FGameplayObjects gameObjects;

		/**
		 *  Timer object for Shot Clock
		 */
		UPROPERTY(BlueprintReadWrite, Category = "Showdown | Clocks")
			FTimerHandle shotClockTimerHandle;

		/**
		 * Current count for the shot clock
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | Clocks")
			float shotClockCount;

		/**
		 *  Timer object for Game Clock
		 */
		UPROPERTY(BlueprintReadWrite, Category = "Showdown | Clocks")
			FTimerHandle gameClockTimerHandle;

		/**
		 * Current count for the shot clock
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | Clocks")
			float gameClockCount;

		/**
		 * Current score count for the home player
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | State")
			int32 scoreHome;

		/**
		 * Current score count for the away player
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | State")
			int32 scoreAway;

		/**
		 * Current value for the weardown bar (in %)
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | State")
			int32 weardownBarPercentage;

		/**
		 * Current possession state
		 */
		UPROPERTY(BlueprintReadOnly, Category = "Showdown | State")
			E_CurrentPossession possession;

		/**
		* Call this function **first** on Begin Play to set references to gameplay objects
		*
		* @param newGameObjects new set of game object refs
		*/
		UFUNCTION(BlueprintCallable, Category = "Showdown | Helpers")
			void RegisterGameObjects(FGameplayObjects newGameObjects);

		/**
		* Call this function to update ball possession
		*
		* @param newPossessionState
		*/
		UFUNCTION(BlueprintCallable, Category = "Showdown | Helpers")
			void UpdateBallPossession(E_CurrentPossession newPossessionState);

		/**
		* Call this function to update the score
		*
		* @param newPossessionState
		*/
		UFUNCTION(BlueprintCallable, Category = "Showdown | Helpers")
			void UpdateScore();

		/**
		* Call this function to update the weardown bar
		*
		* @param newBarPercentage
		*/
		UFUNCTION(BlueprintCallable, Category = "Showdown | Helpers")
			void UpdateBarPercentage(int32 newBarPercentage);


// #region SHOWDOWN INTERFACE

		/**
		* EventScore fires when a shot is made.
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventScore();
			virtual void EventScore_Implementation();

		/**
		* EventShotAttempt fires when a shot at the basket is attempted.
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventShotAttempt();
			virtual void EventShotAttempt_Implementation();

		/**
		* EventShotAttempt fires when a shot at the basket is attempted.
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventBallStateChange(E_BallState NewState);
			virtual void EventBallStateChange_Implementation(E_BallState NewState);

		/**
		* EventOnShotClockEnd fires when the shock clock times out
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventOnShotClockEnd();
			virtual void EventOnShotClockEnd_Implementation();
		
		/**
		* EventOnGameClockEnd fires when the game clock times out
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventOnGameClockEnd();
			virtual void EventOnGameClockEnd_Implementation();

		/**
		* EventOnShotClockStart fires when the shock clock starts
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventOnShotClockStart();
			virtual void EventOnShotClockStart_Implementation();

		/**
		* EventOnGameClockStart fires when the game clock starts
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventOnGameClockStart();
			virtual void EventOnGameClockStart_Implementation();

		/**
		* EventOnRegisterGameObjects fires when the gamestate gets the gameplay refs
		*
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
			void EventOnRegisterGameObjects(FGameplayObjects newGameObjects);
			virtual void EventOnRegisterGameObjects_Implementation(FGameplayObjects newGameObjects);

// #endregion SHOWDOWN INTERFACE
};
