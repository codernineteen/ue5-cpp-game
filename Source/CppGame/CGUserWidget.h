// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGUserWidget.generated.h"

/**
 *
 */
UCLASS()
class CPPGAME_API UCGUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UCGCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UCGCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;

};
