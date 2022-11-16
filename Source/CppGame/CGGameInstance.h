// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CppGame.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "CGGameInstance.generated.h"

USTRUCT()
struct FCGCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCGCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 NextExp;

};

/**
 *
 */

UCLASS()
class CPPGAME_API UCGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UCGGameInstance();

	virtual void Init() override;
	FCGCharacterData* GetCGCharacterData(int32 Level);

private:
	UPROPERTY()
		class UDataTable* CGCharacterTable;
};
