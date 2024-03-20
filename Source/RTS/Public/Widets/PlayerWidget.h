// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	   UFUNCTION(BlueprintImplementableEvent, Category = "WidgetCurrentResource")	// Blueprint Event to Update the Wood Amount.
	void SetDisplayWoodAmount(int32 WoodAmount);

};
