// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/lightInfantry.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"

AlightInfantry::AlightInfantry()
{
	
	ActorAttributesComponent = CreateDefaultSubobject<ULightInfantryAttributesComponent>(TEXT("AttributesComponent"));
	
	// Identify the Worker Drone.
	Tags.Add("LightInfantry");
	
	
}

void AlightInfantry::BeginPlay()
{
	Super::BeginPlay();

	if (SelectionInterface)
	{
		EUnitTypes CurrentUnit = EUnitTypes::LightInfantry;

		// Set the LightInfantryData
		LightInfantryData = SelectionInterface->GetUnitDataForUnit(CurrentUnit);

		UE_LOG(LogTemp, Error, TEXT("SelectionInterface is initialized. LI"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SelectionInterface is not initialized. LI"));
	}
}
