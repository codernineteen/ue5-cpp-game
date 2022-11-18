// Fill out your copyright notice in the Description page of Project Settings.


#include "CGCharacterStatComponent.h"
#include "CGGameInstance.h"

// Sets default values for this component's properties
UCGCharacterStatComponent::UCGCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // true -> false
	bWantsInitializeComponent = true; // false -> true
	
	Level = 1;
}


// Called when the game starts
void UCGCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCGCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UCGCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto CGGameInstance = Cast<UCGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CGCHECK(nullptr != CGGameInstance);
	CurrentStatData = CGGameInstance->GetCGCharacterData(NewLevel);
	if (nullptr != CGGameInstance)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		CGLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UCGCharacterStatComponent::SetDamage(float NewDamage)
{
	CGCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

float UCGCharacterStatComponent::GetAttack()
{
	CGCHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}

void UCGCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChange.Broadcast();


	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}


float UCGCharacterStatComponent::GetHPRatio()
{
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}
