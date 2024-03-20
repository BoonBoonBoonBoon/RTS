// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// Function to Update the Wood Amount.
	//UFUNCTION(BlueprintImplementableEvent, Category = "WidgetCurrentResource")
	//void UpdateWoodAmountText(int32 WoodAmount);	

	virtual bool Initialize() override;

	// The TextBlock Widget for the Wood Amount.
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* WoodAmountTextBlock;

	
	   
	   UFUNCTION(BlueprintImplementableEvent, Category = "WidgetCurrentResource")	// Blueprint Event to Update the Wood Amount.
		void SetDisplayWoodAmount(int32 WoodAmount);
	

};
