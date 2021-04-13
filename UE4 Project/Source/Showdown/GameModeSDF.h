// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Version.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeSDF.generated.h"

/**
 * 
 */
UCLASS()
class SHOWDOWN_API AGameModeSDF : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Gets the version number for this game
	*
	* @param bShortString return the short version of the version number; ex '1.0.0'
	* @return Returns game version
	*/
	UFUNCTION(BlueprintPure, Category = "Showdown Framework | Misc")
		static FString GetGameVersion(UPARAM(DisplayName = "Get Short Version") bool bShortString);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Showdown Framework | Time")
		float gameTimeLimit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Showdown Framework | Time")
		float shotClockTimeLimit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Showdown Framework | Time")
		float actionTimerLimit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Showdown Framework | Time")
		float distanceToGoalMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Showdown Framework | Time")
		float stunBaseTimeLimit;
	
};
