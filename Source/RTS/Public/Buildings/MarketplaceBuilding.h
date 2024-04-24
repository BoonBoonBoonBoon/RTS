// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/MainBuilding.h"
#include "Interfaces/SelectionInterface.h"
#include "MarketplaceBuilding.generated.h"


/**
 * 
 */
UCLASS()
class RTS_API AMarketplaceBuilding : public AMainBuilding
{
	GENERATED_BODY()
public:
	
	AMarketplaceBuilding();

	ISelectionInterface* SelectionInterface;

	virtual void BeginPlay() override;

};
