// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CppGame.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "CGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API ACGPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
};
