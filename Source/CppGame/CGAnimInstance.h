// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CppGame.h"
#include "Animation/AnimInstance.h"
#include "CGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API UCGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCGAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // Tick function for anim instance

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // needs to update in every tick

	
};
