// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShowdownBPFL.generated.h"

/**
*	Enum to codify Gameplay Event
*/
UENUM(BlueprintType)
enum class E_GameplayEvent : uint8 {
	Score,              // 0
	ShotClockTimeOut,	// 1
	GameClockTimeOut,   // 2
	OutOfBounds,        // 3
	StealRecovery,      // 4
};

/**
*	Enum to codify Player States
*/
UENUM(BlueprintType)
enum class E_PlayerState : uint8 {
	Normal,     // 0
	Stunned,	// 1
	Stealing,   // 2
	Countered,  // 3
};


/**
*	Enum to codify Possession States 
*/
UENUM(BlueprintType)
enum class E_CurrentPossession : uint8 {
	Home,   // 0
	Away,	// 1
	None,   // 2   
};

/**
*	Enum to codify Ball States
*/
UENUM(BlueprintType)
enum class E_BallState : uint8 {
	Free,      // 0
	Possessed, // 1
	Shot,      // 2
	Stolen,    // 3
	Swish,     // 4
	Reset      // 5
};

/**
*    Enum for GameState events
*/
UENUM(BlueprintType)
enum class E_GameEvent : uint8 {
	// Shot made
	BasketMade,
	// Shot hit rim
	ReboundOpprotunity,
	// Change possession
	ChangePossession,
	// Defense stole ball;
	BallStolen,
	// Shot clock timed out
	ShotClockTimeout,
	// Game clock timed out
	GameClockTimeout,
	// Start of "round"
	DriveStart,
	// Waiting for Player/AI input
	AwaitingAction,
	// Player failed action
	ActionFailed,
	// Player failed to respond in time
	ActionTimedOut,
	//  Player action was successful
	ActionSuccess,
	// Start of game session
	GameStart,
	// Ready to start gameplay
	Init
};

/**
*    Enum for Player/AI actions
*/
UENUM(BlueprintType)
enum class E_PlayerActions : uint8 {
	Fake,
	BreakAway,
	Shoot,
	Block,
	Pysche,
	Steal,
	None
};


/**
*    Enum for ball possession / team info
*/
UENUM(BlueprintType)
enum class E_Team : uint8 {
	Home,
	Away,
	Free
};

/**
*	Struct to codify Level Objects
*/
USTRUCT(BlueprintType)
struct FGameplayObjects {
	GENERATED_USTRUCT_BODY()

		FGameplayObjects()
		: HomeStartPos()
		, AwayStartPos()
		, BallStartPos()
		, Hoop()
		// TODO: Need to remove the following refs and spawn them in on start
		, HomePlayer()
		, AwayPlayer()
		, Ball()
	{}

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Gameplay")
		FVector HomeStartPos;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Gameplay")
		FVector AwayStartPos;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Gameplay")
		FVector BallStartPos;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Gameplay")
		AActor *Hoop;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Gameplay")
		APlayerController *HomePlayer;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Gameplay")
		AActor *AwayPlayer;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown Framework | Gameplay")
		AActor *Ball;
};

/**
*    Struct to codify Player/AI Action data
*/
USTRUCT(BlueprintType)
struct FShowdownPlayerActionData {
	GENERATED_USTRUCT_BODY()

		FShowdownPlayerActionData()
		: ActionStat(0.0f)
		, ActionTimeReamining(0.0f)
		, Team(E_Team::Home)
		, Action(E_PlayerActions::None)
	{}

	/**
	*    What action was just taken
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float ActionStat;
	/**
	*    How much time was left to take it
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float ActionTimeReamining;

	/**
	*    Which player took action
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		E_Team Team;

	/**
	*    Which action the player took
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		E_PlayerActions Action;

};


/**
*    Struct to codify Player/AI Stats
*/
USTRUCT(BlueprintType)
struct FShowdownPlayerStats {
	GENERATED_USTRUCT_BODY()

		FShowdownPlayerStats()
		: Athleticism(0.0f)
		, Accuracy(0.0f)
		, Defense(0.0f)
		, Handles(0.0f)
		, Vision(0.0f)
		, Drive(0.0f)
	{}

	/**
	*    Effects breakaway chance
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float Athleticism;
	/**
	*    Effects shooting chance
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float Accuracy;

	/**
	*    Effects block chance
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float Defense;

	/**
	*    Effects steal chance
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float Handles;

	/**
	*    Effects fake/psyche chance
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float Vision;

	/**
	*    Effects wear down bar
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		float Drive;
};

/**
*    Struct to codify Player/AI actions
*/
USTRUCT(BlueprintType)
struct FShowdownPlayerActions {
	GENERATED_USTRUCT_BODY()

		FShowdownPlayerActions()
		: CanFake(false)
		, CanBreakAway(false)
		, CanShoot(false)
		, CanBlock(false)
		, CanPysche(false)
		, CanSteal(false)
	{}

	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		bool CanFake;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		bool CanBreakAway;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		bool CanShoot;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		bool CanBlock;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		bool CanPysche;

	UPROPERTY(BlueprintReadWrite, Category = "Showdown | Gameplay")
		bool CanSteal;
};

/**
 *  Home for various structs and helper functions
 */
UCLASS()
class SHOWDOWN_API UShowdownBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
