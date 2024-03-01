// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SelectionInterface.h"

#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Buildings/BarracksBuilding.h"
#include "Buildings/MarketplaceBuilding.h"
#include "Components/DecalComponent.h"

class AGenericBaseAI;

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



EBuildingTypes ISelectionInterface::GetBuildingType(const APawn* Building)
{
	if (Building)
	{
		if (const ABarracksBuilding* BBuilding = Cast<ABarracksBuilding>(Building))
		{
			return GetBuildingType(BBuilding);
		}
		else if (const AMarketplaceBuilding* TBuilding = Cast<AMarketplaceBuilding>(Building))
		{
			return {};
		}
	}
	return {};
}

EBuildingTypes ISelectionInterface::AssignBuildingType(const APawn* Building)
{
	if (Building)
	{
		if (Cast<ABarracksBuilding>(Building))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building type assigned: Barracks"));
			return EBuildingTypes::Barracks;
		}
		else if (Cast<AMarketplaceBuilding>(Building))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building type assigned: Trader"));
			return EBuildingTypes::Trader;
		}
		else if (Cast<AMainBuilding>(Building))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building type assigned: Main"));
			return EBuildingTypes::Invalid;
		}
	}

	return {};
}

void ISelectionInterface::CastTo(APawn* Pawn)
{
	if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
	{
		MainBuilding->SelectedDecalComp->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Array Wiped - Buildings"));
	}
}

void ISelectionInterface::FillArray(TArray<APawn*> Building)
{
	// Adds the selected building to the array
	for (APawn* Pawn : Building)
	{
		if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(true);
			UE_LOG(LogTemp, Warning, TEXT("Building Selected: %s"), *Pawn->GetName());
		}
	}
}

void ISelectionInterface::EmptyArray(TArray<APawn*> Building)
{
	// Deletes the selected building from the array
	for (APawn* Pawn : Building)
	{
		if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(false);
			UE_LOG(LogTemp, Warning, TEXT("Building Deselected: %s"), *Pawn->GetName());
		}
	}

	Building.Empty();
}

EUnitTypes ISelectionInterface::GetUnitType(const AActor* Unit)
{
	return {};
}

UClass* ISelectionInterface::AssignUnitType(const AActor* Unit)
{
	if (Unit)
	{
		// Based on some condition or logic, determine and return the UClass corresponding to the EUnitType
		EUnitTypes UnitType = GetUnitType(Unit);
		switch (UnitType)
		{
		case EUnitTypes::Worker:
			UE_LOG(LogTemp, Warning, TEXT("AssignUnitType - Worker"));
			return AGenericBaseAI::StaticClass();
		case EUnitTypes::Military:
			UE_LOG(LogTemp, Warning, TEXT("AssignUnitType - Military"));
			//return Military::StaticClass();
			break;
		default:
			break;
		}
	}
	return nullptr; // Return nullptr if no unit type is assigned or recognized
	/*if(!Unit)
	{
		return EUnitTypes::Unknown;
	}

	// Check the class of the unit and assign the corresponding unit type.
	if(Unit->IsA(AGenericBaseAI::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("AssignUnitType - Worker"));
		return EUnitTypes::Worker;
	}

	//IF the actors class doesn't match a known unit type, return unknown.
	return EUnitTypes::Unknown;*/
}

/*if (Cast<AGenericBaseAI>(Unit))
	{
		UE_LOG(LogTemp, Warning, TEXT("AssignUnitType - Worker"));
		return EUnitTypes::Worker;
	}
	return {};*/

bool ISelectionInterface::IsBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck)
{
	return BuildingArray.Contains(BuildingToCheck);
}

void ISelectionInterface::UnitSelection()
{
}

void ISelectionInterface::UnitSelection(TArray<AActor*>& Selected, AActor* HitActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Units Pre: %d"), Selected.Num());
	if (Selected.Num() == 0)
	{
		// No units selected, add actor.
		Selected.AddUnique(HitActor);
		for (AActor* Src : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
			{
				BaseAI->SelectedDecalComp->SetVisibility(true);
				UE_LOG(LogTemp, Warning, TEXT("Unit Selection: %d"), Selected.Num());
			}
		}
	}
	// Units already selected, clear previous selection and add the new HitActor
	else
	{
		for (AActor* Pawns : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Pawns))
			{
				BaseAI->SelectedDecalComp->SetVisibility(false);
			}
		}
		// then empties array
		Selected.Empty();
		UE_LOG(LogTemp, Warning, TEXT("Unit Selection (Select.Empty): %d"), Selected.Num());
		// adds the new incoming element
		Selected.AddUnique(HitActor);

		for (AActor* NewPawn : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(NewPawn))
			{
				UE_LOG(LogTemp, Warning, TEXT("Unit Selection (ForLoopAtEnd?): %d"), Selected.Num());
				// sets the new elements vis 
				BaseAI->SelectedDecalComp->SetVisibility(true);
			}
		}
	}
}

void ISelectionInterface::MultiUnitSelection(TArray<AActor*>& Selected, AActor* HitActor)
{
	// Loops through all possible actors 
	Selected.AddUnique(HitActor);
	for (AActor* Src : Selected)
	{
		if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
		{
			BaseAI->SelectedDecalComp->SetVisibility(true);
			UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), Selected.Num());
		}
	}
}

/*if (Selected.Num() == 0)
{
	//UE_LOG(LogTemp, Warning, TEXT("empty"));

	Selected.AddUnique(HitActor);
	for (AActor* Src : Selected)
	{
		if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
		{
			BaseAI->SelectedDecalComp->SetVisibility(true);
			UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), Selected.Num());
		}
	}
}
else
{
	UE_LOG(LogTemp, Warning, TEXT("empty"));

	// Loops through all the elements and turns vis off
	for (AActor* HitActor : Selected)
	{
		if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(HitActor))
		{
			BaseAI->SelectedDecalComp->SetVisibility(false);
		}
	}
	// then empties array
	Selected.Empty();

	// adds the new incoming element
	Selected.AddUnique(HitActor);

	for (AActor* NewPawn : Selected)
	{
		if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(NewPawn))
		{
			// sets the new elements vis 
			BaseAI->SelectedDecalComp->SetVisibility(true);
		}
	}
}*/
