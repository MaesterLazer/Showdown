// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShowdownBPFL.h"
#include "GameModeSDF.h"
#include "InterfaceSDF.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateSDF.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CUSTOM_GameStateSDF, Log, All);
/**
 * 
 */
UCLASS()
class SHOWDOWN_API AGameStateSDF : public AGameStateBase
{
	GENERATED_BODY()
private:

	/**
	 *  Function to start Stun Clock
	 */
	void StartStunClock();

	/**
	 *  Function to advance Stun Clock and increment counter
	 */
	void AdvanceStunClock();

	/**
	 *  Function to end Stun Clock
	 *
	 */
	void EndStunClock();

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
	 *  @param timedOut did the clock time out?
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
	 */
	void EndGameClock();

	/**
	 *  Function to start Action Timer
	 */
	void StartActionTimer();

	/**
	 *  Function to advance Action Timer  and increment counter for ui
	 */
	void AdvanceActionTimer();

	/**
	 *  Function to end Action Timer
	 *
	 *    @param timedOut did the clock time out?
	 */
	void EndActionTimer(bool timedOut);

	/**
	 *  Function to get results for the actions of the players
	 *
	 */
	void GetPlayerActionResults();

	/**
	 *  Function to update score when basket is made
	 *
	 */
	void UpdateScore();

	/**
	 *  Get distance to the basket from where the player is attempting to shoot
	 *
	 * @return float added to failure threshold
	 */
	float GetDistanceToBasketModifier();

public:

	/**
	 *  BeginPlay override
	 */
	UFUNCTION(BlueprintCallable)
		virtual void BeginPlay() override;

	/**
	 *  Pointer for Showdown GameMode
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | GameplayElements")
		AGameModeSDF * GameMode;

	/**
	 *  Pointer for game objects
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | GameplayElements")
		FGameplayObjects gameObjects;


	/**
	 * Assign pointers to various gameplay objects
	 * @param objs gameplay objects
	*/
	UFUNCTION(BlueprintCallable, Category = "Showdown Framework | Gameplay")
		void RegisterGameObjects(FGameplayObjects objs);

	/**
	 * Stun or remove stun on possessing player
	 * @param bDisableStun disable/enable effect
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Showdown Framework | Gameplay")
		void OnStunPossessingPlayer(bool bDisableStun);
	virtual void OnStunPossessingPlayer_Implementation(bool bDisableStun);

	/**
	 *  Timer object for Shot Clock
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Clocks")
		FTimerHandle stunTimerHandle;

	/**
	 * Current count for the stun effect
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | Clocks")
		float stunTimeCount;

	/**
	 *  Timer object for Shot Clock
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Clocks")
		FTimerHandle shotClockTimerHandle;

	/**
	 * Current count for the shot clock
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | Clocks")
		float shotClockCount;

	/**
	 *  Timer object for Game Clock
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Clocks")
		FTimerHandle gameClockTimerHandle;

	/**
	 * Current count for the shot clock
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | Clocks")
		float gameClockCount;

	/**
	 *  Timer object for Action  Timer
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Clocks")
		FTimerHandle actionTimerHandle;

	/**
	 * Current count for the shot clock
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | Clocks")
		float actionTimerCount;

	/**
	 * Current score count for the home player
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		int32 scoreHome;

	/**
	 * Current score count for the away player
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		int32 scoreAway;

	/**
	 * Current possession state
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		E_Team possession;

	/**
	 * Current home player action data
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		FShowdownPlayerActionData homePlayerData;

	/**
	 * Current action data for Player1
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		FShowdownPlayerActionData homePlayerActionData;

	/**
	 * Current action data for Player2/AI
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		FShowdownPlayerActionData awayPlayerActionData;

	/**
	 * Has player 1 taken a action ?
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		bool homePlayerTakenAction;

	/**
	 * Has player 2/ AI taken a action ?
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Showdown Framework | State")
		bool awayPlayerTakenAction;

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
	 * OnActionAttempt fires when an action is attempted.
	 * @param Action the action that the player took with relevant info
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnActionAttempt(FShowdownPlayerActionData Action);
	virtual void OnActionAttempt_Implementation(FShowdownPlayerActionData Action);

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

	// #endregion SHOWDOWN INTERFACE
	
};
