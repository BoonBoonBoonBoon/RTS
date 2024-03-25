// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SelectionInterface.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/lightInfantry.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Buildings/BarracksBuilding.h"
#include "Buildings/MarketplaceBuilding.h"
#include "Components/DecalComponent.h"


class IUnitInterface;
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

EBuildingTypes ISelectionInterface::GetBuildingType(const AActor* Building)
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

EBuildingTypes ISelectionInterface::AssignBuildingType(const AActor* Building)
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

void ISelectionInterface::CastTo(AActor* Pawn)
{
	if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
	{
		MainBuilding->SelectedDecalComp->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Array Wiped - Buildings"));
	}
}

void ISelectionInterface::FillArray(TArray<AActor*> Building)
{
	// Adds the selected building to the array
	for (AActor* Pawn : Building)
	{
		if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(true);
			UE_LOG(LogTemp, Warning, TEXT("Building Selected: %s"), *Pawn->GetName());
		}
	}
}

void ISelectionInterface::EmptyArray(TArray<AActor*> Building)
{
	// Deletes the selected building from the array
	for (AActor* Pawn : Building)
	{
		if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(false);
			UE_LOG(LogTemp, Warning, TEXT("Building Deselected: %s"), *Pawn->GetName());
		}
	}

	Building.Empty();
}

bool ISelectionInterface::IsBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck)
{
	return BuildingArray.Contains(BuildingToCheck);
}

void ISelectionInterface::UnitSelection()
{
}

void ISelectionInterface::UnitSelection(TArray<AActor*>& Selected, AActor* HitActor)
{
	// If Array is empty
	if (Selected.IsEmpty())
	{
		// S Array is empty, add actor.
		Selected.AddUnique(HitActor);
		for (AActor* Src : Selected)
		{
			if (const AGenericBaseAI* AI = Cast<AGenericBaseAI>(Src))
			{
				AI->SelectedDecalComp->SetVisibility(true);

				// Determines Unit EUnitType.
				HandleTypes(Selected, HitActor);
			}
		}
	} else
	{
		ChangeElementInArray(Selected, HitActor);
	}
}

void ISelectionInterface::BuildingArrayIsEmpty(TArray<AActor*>& Building, AActor* HitPawn)
{
	if (Building.IsEmpty())
	{
		Building.AddUnique(HitPawn);
		for (AActor* SrcP : Building)
		{
			if (const AMainBuilding* MBuilding = Cast<AMainBuilding>(SrcP))
			{
				MBuilding->SelectedDecalComp->SetVisibility(true);
			}
		}
	}
}

void ISelectionInterface::ChangeElementInArray(TArray<AActor*>& Array, AActor* HitPawn)
{
	if(Array.Num() > 0)
	{
		for(AActor* Actor : Array) 
		{
			if(const AMainBuilding* MBuilding = Cast<AMainBuilding>(Actor))
			{
				MBuilding->SelectedDecalComp->SetVisibility(false);
				Array.Empty(); 
				
				Array.AddUnique(HitPawn); 
				for(AActor* SrcP : Array) 
				{
					if(const AMainBuilding* NewBuilding = Cast<AMainBuilding>(SrcP)) 
					{
						NewBuilding->SelectedDecalComp->SetVisibility(true); 
					}
				}
			} else if(const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Actor))
			{
				BaseAI->SelectedDecalComp->SetVisibility(false);
				Array.Empty(); 
				
				Array.AddUnique(HitPawn); 
				for(AActor* Src : Array) 
				{
					if(const AGenericBaseAI* NewBaseAI = Cast<AGenericBaseAI>(Src)) 
					{
						NewBaseAI->SelectedDecalComp->SetVisibility(true);
						HandleTypes(Array, HitPawn);
					}
				}
			}
		}
	}
}

void ISelectionInterface::MultiUnitSelection(TArray<AActor*>& Selected, AActor* HitActor)
{
	if(Cast<AGenericBaseAI>(HitActor))
	{
		// Loops through all possible actors 
		Selected.AddUnique(HitActor);
		for (AActor* Src : Selected)
		{
			if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
			{
				BaseAI->SelectedDecalComp->SetVisibility(true);

				HandleTypes(Selected, HitActor);
			}
		}
	} 
}

void ISelectionInterface::NotHit(TArray<AActor*> &Array)
{
	// Loops through all the elements and turns vis off
	for(AActor* PawnSrc : Array)
	{
		if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(PawnSrc))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(false);
			Array.Empty();
		} else if(const AGenericBaseAI* AI = Cast<AGenericBaseAI>(PawnSrc))
		{
			AI->SelectedDecalComp->SetVisibility(false);
			Array.Empty();
		}
	}
}

bool ISelectionInterface::IsUnitSelected(const TArray<AActor*>& UnitArray, const AActor* UnitToCheck)
{
	return UnitArray.Contains(UnitToCheck);
}

void ISelectionInterface::HandleTypes(const TArray<AActor*>& UnitArray, const AActor* UnitActor)
{
	// Checks validity of the unit.
	if (IsUnitSelected(UnitArray, UnitActor))
	{
		// Determines the type of unit.
		if (const EUnitTypes UnitType = GetUnitType(UnitActor); UnitType == EUnitTypes::Worker)
		{
			GetAttributesForunit(UnitType);
			UE_LOG(LogTemp, Warning, TEXT("Unit Type: Worker"));
		}
		else if (UnitType == EUnitTypes::LightInfantry)
		{
			UE_LOG(LogTemp, Warning, TEXT("Unit Type: Light Infantry"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unit Type: Invalid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Element Is Not in the Array."));
	}
}

EUnitTypes ISelectionInterface::GetUnitType(const AActor* UnitActor)
{
	if (UnitActor)
	{
		if (Cast<AWorkerDrone>(UnitActor))
		{
			// Define the attributes of the unit.
			DefineAttributes(UnitActor, EUnitTypes::Worker); // FIRST STEP, WE FIND THE UNIT TYPE
			return EUnitTypes::Worker;
		}
		else if (Cast<AlightInfantry>(UnitActor))
		{
			DefineAttributes(UnitActor, EUnitTypes::Worker);
			return EUnitTypes::LightInfantry;
		}
	}
	return EUnitTypes::Invalid;
}

void ISelectionInterface::DefineAttributes(const AActor* UnitActor, EUnitTypes UnitTypes)
{
	if(UnitTypes== EUnitTypes::Worker)
	{
		GetAttributesForunit(UnitTypes); // ONCE FIGURED OUT UNIT TYPE WE WANT TO ASSIGN IT ATTRIBUTES.
		UE_LOG(LogTemp, Warning, TEXT("Worker Attributes Defined."));
	}
	else if(UnitTypes == EUnitTypes::LightInfantry)
	{
		UE_LOG(LogTemp, Warning, TEXT("Light Infantry Attributes Defined."));
	}
}

TArray<EUnitAttributes> ISelectionInterface::GetAttributesForunit(EUnitTypes UnitTypes)
{
	// Map of unit types to attributes.
	UnitTypeToAttributesMap = {
		{EUnitTypes::Worker, {EUnitAttributes::Gather, EUnitAttributes::Repair, EUnitAttributes::Build}},
		{EUnitTypes::LightInfantry, {EUnitAttributes::Attack, EUnitAttributes::Guard, EUnitAttributes::Patrol}}
	};
	return {UnitTypeToAttributesMap[UnitTypes]}; // ????? RETURNS THE ATTRIBUTES OF THE UNIT.
	// Maybe we dont need a return statement here.
	// instead make it void?
	
}

/*
TArray<EUnitAttributes> ISelectionInterface::FindUnitAttributes(EUnitTypes UnitTypes, TArray<EUnitAttributes>& UnitAttributes)
{
	// Returns the attributes of the unit.
	if (const TArray<EUnitAttributes>* Attributes = UnitTypeToAttributesMap.Find(UnitTypes))
	{
		return *Attributes;
	}
	return {};
}

// Function to convert EUnitTypes enum to string
FString ISelectionInterface::EnumToString(EUnitTypes EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EUnitTypes"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetNameStringByValue((int64)EnumValue);
}

// Function to convert EUnitAttributes enum to string
FString ISelectionInterface::EnumToString(EUnitAttributes EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EUnitAttributes"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetNameStringByValue((int64)EnumValue);
}

void ISelectionInterface::LogUnitTypeToAttributesMap(TMap<EUnitTypes, TArray<EUnitAttributes>> AttributesMap)
{
	// Iterate over each key-value pair in the map
	for (const auto& Pair : AttributesMap)
	{
		// Convert the key (Unit Type) to string
		FString UnitTypeString = EnumToString(Pair.Key);

		// Start building the string for the value (Attributes Array)
		FString AttributesString = TEXT("[");
		for (const EUnitAttributes& Attribute : Pair.Value)
		{
			// Append each attribute to the string
			AttributesString += EnumToString(Attribute) + TEXT(", ");
		}
		// Remove the trailing comma and space if there are any attributes
		if (Pair.Value.Num() > 0)
		{
			AttributesString.RemoveAt(AttributesString.Len() - 2);
		}
		AttributesString += TEXT("]");

		// Log the key-value pair
		UE_LOG(LogTemp, Log, TEXT("%s: %s"), *UnitTypeString, *AttributesString);
	}
}
*/
