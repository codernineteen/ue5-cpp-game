// Fill out your copyright notice in the Description page of Project Settings.


#include "CGUserWidget.h"
#include "CGCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UCGUserWidget::BindCharacterStat(UCGCharacterStatComponent* NewCharacterStat)
{
	CGCHECK(nullptr != NewCharacterStat);
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChange.AddUObject(this, &UCGUserWidget::UpdateHPWidget);
}

void UCGUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	CGCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}

void UCGUserWidget::UpdateHPWidget()
{
	CGLOG_S(Warning);
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}