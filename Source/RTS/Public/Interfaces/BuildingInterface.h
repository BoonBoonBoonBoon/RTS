// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API IBuildingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Its he type VVVV Figure out a way to do it without EbuildingTypes or something?????
	// Maybe aadd parameter?
	//static EBuildingTypes GetBuildingType(AMainBuilding* Building);
	
	//void BuildingSelection(APawn* HitObject, AController* Controller);
	
	// Units are purchased
	void PurchaseUnit();
	// Units are spawned
	void SpawnUnit();
	// Purchase Materials from trader
	void PurchaseGoods();

	bool bHasSelectedBuild = false; // Empties array for building
};

// Types of Buildings
UENUM(BlueprintType)
enum class  EBuildingTypes : uint8
{
	Hall,
	Barracks,
	Trader,
	Invalid
};

const char* to_string(EBuildingTypes e);
