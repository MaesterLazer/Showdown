// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPFL1v1.h"
#include "UObject/Interface.h"
#include "Interface1v1.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface1v1 : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOWDOWN_API IInterface1v1
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	* EventOnBallStateChange fires when there is a change in the Ball object state. 
	*
	* @param NewState new state of the ball
	*/

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interfaces|Interface1v1")
		void EventOnBallStateChange(E_BallState NewState);

};
