// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameMode.h"
#include "CGCharacter.h"
#include "CGPlayerController.h"

ACGGameMode::ACGGameMode() {
	DefaultPawnClass = ACGCharacter::StaticClass();
	PlayerControllerClass = ACGPlayerController::StaticClass();
	//Set default pawn
	/*static ConstructorHelpers::FClassFinder<APawn> BP_THIRD_PAWN_C(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter"));

	if (BP_THIRD_PAWN_C.Succeeded()) {
		DefaultPawnClass = BP_THIRD_PAWN_C.Class;
	}*/
}

void ACGGameMode::PostLogin(APlayerController* NewPlayer) {
	CGLOG(Warning, TEXT("Post Login Start"));
	Super::PostLogin(NewPlayer);
	CGLOG(Warning, TEXT("Post Login End"))
}
