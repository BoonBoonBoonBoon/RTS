// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/BuildingInterface.h"
/*#include "Buildings/BarracksBuilding.h"
#include "Buildings/MainBuilding.h"
#include "Buildings/MarketplaceBuilding.h"
#include "Components/DecalComponent.h"*/


/*EBuildingTypes IBuildingInterface::GetBuildingType(const APawn* Building)
{
	if(Building)
	{
		if(const ABarracksBuilding* BBuilding = Cast<ABarracksBuilding>(Building))
		{
			return GetBuildingType(BBuilding);
		}
		else if(const AMarketplaceBuilding* TBuilding = Cast<AMarketplaceBuilding>(Building))
		{
			return {};
		}
	}
	return {};
}

EBuildingTypes IBuildingInterface::AssignBuildingType(const APawn* Building)
{
	if(Building)
	{
		if(Cast<ABarracksBuilding>(Building))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building type assigned: Barracks"));
			return EBuildingTypes::Barracks;
		}
		else if(Cast<AMarketplaceBuilding>(Building))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building type assigned: Trader"));
			return EBuildingTypes::Trader;
		}
		else if(Cast<AMainBuilding>(Building))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building type assigned: Main"));
			return EBuildingTypes::Invalid;
		}
	}
	
	return {};
}

void IBuildingInterface::CastTo(APawn* Pawn)
{
	if(const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
	{
		MainBuilding->SelectedDecalComp->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Array Wiped - Buildings"));
	}
}


void IBuildingInterface::FillArray(TArray<APawn*> Building)
{
	// Adds the selected building to the array
	for (APawn* Pawn : Building)
	{
		if(const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(true);
			UE_LOG(LogTemp, Warning, TEXT("Building Selected: %s"), *Pawn->GetName());
		}
	}
}

void IBuildingInterface::EmptyArray(TArray<APawn*> Building)
{
	// Deletes the selected building from the array
	for(APawn* Pawn : Building)
	{
		if(const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(false);
			UE_LOG(LogTemp, Warning, TEXT("Building Deselected: %s"), *Pawn->GetName());
		}
	}
	
	Building.Empty();
}

bool IBuildingInterface::IsBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck)
{
	// Check if the BuildingToCheck is present in the BuildingArray
	return BuildingArray.Contains(BuildingToCheck);
}



void IBuildingInterface::PurchaseUnit()
{
}

// Add default functionality here for any IBuildingInterface functions that are not pure virtual.
void IBuildingInterface::SpawnUnit()
{

}

void IBuildingInterface::PurchaseGoods()
{
	
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
	
}*/
