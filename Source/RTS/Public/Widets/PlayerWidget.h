// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */

/*
UENUM()
enum class EHudViewMode : uint8
{
	Clean UMeta(ToolTip= "Clean"),
	Minimal UMeta(ToolTip = "Minimal"),
	Moderate UMeta(ToolTip = "Moderate"),
	Full UMeta(ToolTip = "Full")
};
*/


UCLASS()
class RTS_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	// The TextBlock Widget for the Wood Amount.
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WoodAmountTextBlock;
	   
	UFUNCTION(BlueprintCallable, Category = "WidgetCurrentResource")	// Blueprint Event to Update the Wood Amount.
	void SetDisplayWoodAmount(int32 WoodAmount);

private:
	
	/*
	// Determines the View Mode of the HUD.
	UPROPERTY(EditAnywhere)
	EHudViewMode CurrentViewMode = EHudViewMode::Moderate;
	*/

};
