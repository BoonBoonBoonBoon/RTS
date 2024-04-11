// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Heavy/HeavyInfantry/HeavyInfantry.h"

AHeavyInfantry::AHeavyInfantry()
{

	HeavyInfantryAttributesComponent = CreateDefaultSubobject<UHeavyInfantryAttributesComponent>(TEXT("AttributesComponent"));
	
	Tags.Add("HeavyInfantry");
}

void AHeavyInfantry::BeginPlay()
{
	Super::BeginPlay();

	if (SelectionInterface)
	{
		// Assigns the UnitType as a Worker.
		UnitType = SelectionInterface->GetUnitType(this);

		// Obtains The Unit Data for the Current Unit (Attributes & Stats).
		UnitData = SelectionInterface->GetUnitDataForUnit(UnitType);

		// Adds the Currently Obtained Unit Data to the Unit Data Map.
		// UnitDataMap Now stores the current Type of Unit and its Data.
		UnitDataMap.Add(UnitType, UnitData);

		// Logs the Data we assigned to the unit.
		SelectionInterface->LogUnitTypeToDataMap(UnitDataMap);
	}
}
