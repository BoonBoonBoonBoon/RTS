// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"

AWorkerDrone::AWorkerDrone()
{
	// Obtain the Unit Type we are working with.
	UnitType = EUnitTypes::Worker;
	
	WorkerAttributesComponent = CreateDefaultSubobject<UWorkerAttributesComponent>(TEXT("AttributesComponent"));
	
	// Identify the Worker Drone.
	Tags.Add("WorkerDrone");
	
}

void AWorkerDrone::BeginPlay()
{
	Super::BeginPlay();

// TODO : Doesn't Work. Needs to be Instantiated.
	
	// Get the Unit Data for the Current Unit.
	if (SelectionInterface)
	{
		UnitData = SelectionInterface->GetUnitDataForUnit(UnitType);

		if (SelectionInterface->UnitTypeToDataMap.Contains(UnitType)) // Check if the TMap Contains a valid unit type.
		{
			// Then assign the attributes of the unit to the new Attribute TArray. If the unit has the Gather attribute, then it can gather resources.
			if (TArray<EUnitAttributes> Att = SelectionInterface->UnitTypeToDataMap[UnitType].Attributes; Att.Contains(EUnitAttributes::Gather))
			{
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
}
	
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
