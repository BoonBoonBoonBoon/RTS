// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/BuildingInterface.h"
#include "Buildings/MainBuilding.h"
#include "Components/DecalComponent.h"


EBuildingTypes IBuildingInterface::GetBuildingType(AMainBuilding* Building)
{
	if (Building)
	{
		return Building->BuildingType;
	}
	// Return a default value or an "invalid" type if needed
	return EBuildingTypes::Invalid;
}

void IBuildingInterface::BuildingSelection(APawn* HitObject, AController* Controller)
{
	if (AUserController* UserController = Cast<AUserController>(Controller))
	{
		// Clear out selected
		UserController->SelectedUnits.Empty();

		// add in new unit
		UserController->SelectedUnits.AddUnique(HitObject);
		for (AActor* Src : UserController->SelectedUnits)
		{
			if (const AMainBuilding* Building = Cast<AMainBuilding>(Src))
			{
				//Building->SelectedDecalComp->SetVisibility(true);
				//UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), UserController->SelectedUnits.Num());
			}
		}
	}
}


void IBuildingInterface::PurchaseUnit()
{
}

// Add default functionality here for any IBuildingInterface functions that are not pure virtual.
void IBuildingInterface::SpawnUnit()
{
	UE_PRIVATE_LOG(PREPROCESSOR_NOTHING, constexpr, LogTemp, Warning, L"Building Is Barracks & Has interface ");
}

void IBuildingInterface::PurchaseGoods()
{
	UE_PRIVATE_LOG(PREPROCESSOR_NOTHING, constexpr, LogTemp, Warning, L"Building Is Trader & Has interface ");
}
