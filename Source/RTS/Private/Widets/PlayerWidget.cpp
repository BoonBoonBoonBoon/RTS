// Fill out your copyright notice in the Description page of Project Settings.


#include "Widets/PlayerWidget.h"
#include "Components/TextBlock.h"

bool UPlayerWidget::Initialize()
{
	Super::Initialize();
	return true;
}

void UPlayerWidget::SetDisplayWoodAmount(int32 WoodAmount)
{
	if(WoodAmountTextBlock)
	{
	const FText TextValue = FText::Format(FText::FromString(TEXT("Wood : {0}")), FText::AsNumber(WoodAmount));
		WoodAmountTextBlock->SetText(TextValue);
	}
}
