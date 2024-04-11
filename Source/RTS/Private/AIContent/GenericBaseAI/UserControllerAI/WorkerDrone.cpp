// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"

AWorkerDrone::AWorkerDrone()
{
	WorkerAttributesComponent = CreateDefaultSubobject<UWorkerAttributesComponent>(TEXT("AttributesComponent"));
	
	// Identify the Worker Drone.
	Tags.Add("WorkerDrone");

	
	
}

void AWorkerDrone::BeginPlay()
{
	Super::BeginPlay();

	if(SelectionInterface)
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


// Obtains and Assigns the 
//UnitDataMap = SelectionInterface->UnitTypeToDataMap;

// Obtain the Unit Type we are working with.
//WorkerType = EUnitTypes::Worker;
	

/*
// Get the Unit Data for the Current Unit.
if (SelectionInterface)
{
	UE_LOG(LogTemp, Warning, TEXT("SI WorkerDrone Initialized."));
		
	WorkerDroneData = SelectionInterface->GetUnitDataForUnit(WorkerType);

	if (UnitTypeToDataMap.Contains(WorkerType)) // Check if the TMap Contains a valid unit type.
	{
			
		UE_LOG(LogTemp, Warning, TEXT("Contains WorkerType"));
			
		// Then assign the attributes of the unit to the new Attribute TArray. If the unit has the Gather attribute, then it can gather resources.
		if (TArray<EUnitAttributes> Att = SelectionInterface->UnitTypeToDataMap[WorkerType].Attributes; Att.Contains(EUnitAttributes::Gather))
		{

			UE_LOG(LogTemp, Warning, TEXT("Contains Gather Attribute."));
				
			// Find the component of the current incoming unit object.
			if (UWorkerAttributesComponent* ActorAttributes = FindComponentByClass<UWorkerAttributesComponent>())
			{
				ActorAttributes->SetCanGather(true);
				UE_LOG(LogTemp, Warning, TEXT("Can Gather Resources"));
			}
		}
	}
}
else
{
	//UE_LOG(LogTemp, Error, TEXT("SelectionInterface is not initialized."));
}
*/






	/*if (SelectionInterface)
	{
		// Get the Unit Data for the Current Unit.
		UnitData = SelectionInterface->GetUnitDataForUnit(UnitType);

		if (this->SelectionInterface->UnitTypeToDataMap.Contains(UnitType))
		// Check if the TMap Contains a valid unit type.
		{
			// Then assign the attributes of the unit to the new Attribute TArray. If the unit has the Gather attribute, then it can gather resources.
			if (TArray<EUnitAttributes> Att = this->SelectionInterface->UnitTypeToDataMap[UnitType].Attributes; Att.
				Contains(EUnitAttributes::Gather))
			{
				// Find the component of the current incoming unit object.
				if (UWorkerAttributesComponent* ActorAttributes = this->FindComponentByClass<
					UWorkerAttributesComponent>())
				{
					ActorAttributes->SetCanGather(true);
					UE_LOG(LogTemp, Warning, TEXT("Can Gather Resources"));
				}
			}
		}
	}*/
//}
