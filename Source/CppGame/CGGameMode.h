// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CppGame.h"
#include "GameFramework/GameModeBase.h"
#include "CGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API ACGGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ACGGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
