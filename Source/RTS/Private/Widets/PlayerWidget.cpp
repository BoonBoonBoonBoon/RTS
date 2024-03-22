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

	UE_LOG(LogTemp, Warning, TEXT("SetDisplay"));

	WoodAmountUpdated.Broadcast(); // Calls the Blueprint Event to Update the Wood Amount.
	
	//if(WoodAmountTextBlock)
	//{
		/*// Format the text to include "Wood :" and the current wood amount.
		const FText TextValue = FText::Format(
			FText::FromString(TEXT("Wood : {0}")), FText::AsNumber(WoodAmount)
			);
		UE_LOG(LogTemp, Warning, TEXT("Debug Amoount : %d"), WoodAmount);
		WoodAmountTextBlock->SetText(TextValue); // Set the Text Value.
	//}*/
}
