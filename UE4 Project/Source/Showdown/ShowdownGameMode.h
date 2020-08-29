// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Version.h"
#include "ShowdownInterface.h"
#include "GameFramework/GameModeBase.h"
#include "ShowdownGameMode.generated.h"

/**
 * GameModeBase subclass for the Showdown Game.
 */
UCLASS()
class SHOWDOWN_API AShowdownGameMode : public AGameModeBase, public IShowdownInterface
{
	GENERATED_BODY()
	
public:
		/** Gets the version number for this game
		*
		* @param bShortString return the short version of the version number; ex '1.0.0'
		* @return Returns game version
		*/
		UFUNCTION(BlueprintPure, Category = "ShowdownGameMode | Misc")
			static FString GetGameVersion(UPARAM(DisplayName = "Get Short Version") bool bShortString);

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShowdownGameMode | Time")
			float gameTimeLimit;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShowdownGameMode | Time" )
			float shotClockTimeLimit;



};
