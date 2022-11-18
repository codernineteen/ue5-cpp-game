// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameInstance.h"

UCGGameInstance::UCGGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/GameData/ABCharacterData.ABCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CGCHARACTERDATA(*CharacterDataPath);
	CGCHECK(DT_CGCHARACTERDATA.Succeeded());
	CGCharacterTable = DT_CGCHARACTERDATA.Object;
}


void UCGGameInstance::Init()
{
	Super::Init();

}

FCGCharacterData* UCGGameInstance::GetCGCharacterData(int32 Level)
{
	return CGCharacterTable->FindRow<FCGCharacterData>(*FString::FromInt(Level), TEXT(""));
}
