// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPlayerController.h"

void ACGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CGLOG_S(Warning);
}

void ACGPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}