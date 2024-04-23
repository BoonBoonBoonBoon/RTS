// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWOODAMOUNTUPDATEDSIGNATURE);

/**
 * @class UPlayerWidget
 * @brief A class that represents the player's widget in the game.
 *
 * This class is a Blueprintable and BlueprintType class, which means it can be subclassed in Blueprints and its instances can be created and manipulated in Blueprints.
 * It belongs to the 'Custom' class group, which is a user-defined group that can be used to organize classes in the Unreal Editor.
 * The BlueprintSpawnableComponent meta tag indicates that instances of this class can be added to Blueprint actors directly from the Components panel in the Blueprint Editor.
 *
 * @extends UUserWidget
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RTS_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	
	/*
	UPROPERTY(BlueprintType, BlueprintAssignable)
	FWOODAMOUNTUPDATEDSIGNATURE WoodAmountUpdated;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
	void UpdateWoodAmount(int32 NewAmount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
	void UpdateStoneAmount(int32 NewAmount);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
	void UpdateFoodAmount(int32 NewAmount);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
	void UpdateGoldAmount(int32 NewAmount);
	*/
	
	
	virtual bool Initialize() override;

	// The TextBlock Widget for the Wood Amount.
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WoodAmountTextBlock;

	UPROPERTY(Blueprintable, BlueprintReadWrite)
	TObjectPtr<UPlayerWidget> ThisWidget;
	


private:
	

};
