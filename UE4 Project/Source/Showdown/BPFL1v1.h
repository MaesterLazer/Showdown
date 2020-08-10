// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL1v1.generated.h"

/**
 * 
 */

 // Enum to codify Ball States
UENUM(BlueprintType)
enum class E_BallState : uint8 {
	Free,      // 0
	Possessed, // 1
	Shot,      // 2
	Stolen,    // 3
	Swish,     // 4
	Reset      // 5
};

UCLASS()
class SHOWDOWN_API UBPFL1v1 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
