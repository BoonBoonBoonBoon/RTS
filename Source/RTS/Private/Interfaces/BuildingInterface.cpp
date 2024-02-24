// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/BuildingInterface.h"
#include "Buildings/BarracksBuilding.h"
#include "Buildings/MainBuilding.h"
#include "Buildings/MarketplaceBuilding.h"


EBuildingTypes IBuildingInterface::GetBuildingType(const APawn* Building)
{
	if(Building)
	{
 		if(const AMainBuilding* MBuilding = Cast<AMainBuilding>(Building))
		{
			return GetBuildingType(MBuilding);
		}
		else if(const ABarracksBuilding* BBuilding = Cast<ABarracksBuilding>(Building))
		{
			return GetBuildingType(BBuilding);
		}
		else if(const AMarketplaceBuilding* TBuilding = Cast<AMarketplaceBuilding>(Building))
		{
			return GetBuildingType(TBuilding);
		}
		
	}
	return {};
}

/*EBuildingTypes IBuildingInterface::AssignBuildingType(const APawn* Building)
{
	if(Building)
	{
		if(const AMainBuilding* MBuilding = Cast<AMainBuilding>(Building))
		{
			return EBuildingTypes::Invalid;
		}
		else if(const ABarracksBuilding* BBuilding = Cast<ABarracksBuilding>(Building))
		{
			return EBuildingTypes::Barracks;
		}
		else if(const AMarketplaceBuilding* TBuilding = Cast<AMarketplaceBuilding>(Building))
		{
			return EBuildingTypes::Trader;
		}
	}
	return {};
}*/


/*
if (Building)
{
	//return EBuildingTypes::Invalid;
}
// Return a default value or an "invalid" type if needed
return EBuildingTypes::Invalid;
*/



/*void IBuildingInterface::BuildingSelection(APawn* HitObject, AController* Controller)
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
}*/


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
	//UE_PRIVATE_LOG(PREPROCESSOR_NOTHING, constexpr, LogTemp, Warning, L"Building Is Trader & Has interface ");
}

const char* to_string(EBuildingTypes e)
{
	switch (e)
	{
	case EBuildingTypes::Hall: return "Hall";
	case EBuildingTypes::Barracks: return "Barracks";
	case EBuildingTypes::Trader: return "Trader";
	case EBuildingTypes::Invalid: return "Invalid";
	default: return "unknown";
	}
}

IBuildingInterface::IBuildingInterface()
{
}
