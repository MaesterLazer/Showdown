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

	UPROPERTY(BlueprintReadWrite, Category = "GameplayObjects")
		FVector HomeStartPos;

	UPROPERTY(BlueprintReadWrite, Category = "GameplayObjects")
		FVector AwayStartPos;

	UPROPERTY(BlueprintReadWrite, Category = "GameplayObjects")
		FVector BallStartPos;

	UPROPERTY(BlueprintReadWrite, Category = "GameplayObjects")
		AActor *Hoop;

	UPROPERTY(BlueprintReadWrite, Category = "GameplayObjects")
		AActor *HomePlayer;

	UPROPERTY(BlueprintReadWrite, Category = "GameplayObjects")
		AActor *AwayPlayer;

	UPROPERTY(BlueprintReadWrite, Category = "GameplayObjects")
		AActor *Ball;
};



UCLASS()
class SHOWDOWN_API UShowdownBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
