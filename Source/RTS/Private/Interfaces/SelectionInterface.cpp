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


bool ISelectionInterface::IsBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck)
{
	return BuildingArray.Contains(BuildingToCheck);
}

void ISelectionInterface::UnitSelection()
{
}

void ISelectionInterface::UnitSelection(TArray<AActor*>& Selected, TArray<APawn*>& PSelected, AActor* HitActor)
{
	UE_LOG(LogTemp, Warning, TEXT("I)L: 154 - Units Pre: %d"), Selected.Num());
	UE_LOG(LogTemp, Warning, TEXT("I)L: 155 - Buildings Pre: %d"), PSelected.Num());

	// If S Array or PS Array is empty
	if (Selected.IsEmpty() || PSelected.IsEmpty())
	{
		// PS Array is empty, add actor.
		PSelected.AddUnique(Cast<APawn>(HitActor));
		for (APawn* SrcP : PSelected)
		{
			if (AMainBuilding* MBuilding = Cast<AMainBuilding>(SrcP))
			{
				UE_LOG(LogTemp, Warning, TEXT("I)L: 166 - Building Set Visibility to True: %d"), PSelected.Num());
				MBuilding->SelectedDecalComp->SetVisibility(true);
			}
		}
		
		// S Array is empty, add actor.
		Selected.AddUnique(HitActor);
		for (AActor* Src : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
			{
				UE_LOG(LogTemp, Warning, TEXT("I)L: 177 - AI Set Visibility to True: %d"), Selected.Num());
				BaseAI->SelectedDecalComp->SetVisibility(true);
			}
		}
		
		/*} else if(PSelected.IsEmpty())
		{
			PSelected.AddUnique(Cast<APawn>(HitActor));
			for (AActor* Src : PSelected)
			{
				if (AMainBuilding* MBuilding = Cast<AMainBuilding>(Src))
				{
					MBuilding->SelectedDecalComp->SetVisibility(true);
					UE_LOG(LogTemp, Warning, TEXT("Buildings Selection: %d"), PSelected.Num());
				}
			}
		}*/
		// Units already selected, clear previous selection and add the new HitActor
	}
}

void ISelectionInterface::SwapActor(TArray<AActor*>& Selected, TArray<APawn*>& PSelected, AActor* HitActor)
{
	if (Selected.Num() >= 1 || PSelected.Num() >= 1)
	{
		for (APawn* Pawns : PSelected)
		{
			if (AMainBuilding* MBuilding = Cast<AMainBuilding>(Pawns))
			{
				MBuilding->SelectedDecalComp->SetVisibility(false);
			}
		}

		for (AActor* Actors : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Actors))
			{
				BaseAI->SelectedDecalComp->SetVisibility(false);
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("I)L:213 - If Select Array has something in it : %d"), Selected.Num());
		UE_LOG(LogTemp, Warning, TEXT("I)L:214 - If PSelect Array has something in it : %d"), PSelected.Num());

		// then empties array
		Selected.Empty();
		PSelected.Empty();

		// adds the new incoming element
		Selected.AddUnique(HitActor);
		PSelected.AddUnique(Cast<APawn>(HitActor));


		UE_LOG(LogTemp, Warning, TEXT("I)L:220 - AddUniqe Select : %d"), Selected.Num());
		UE_LOG(LogTemp, Warning, TEXT("I)L:222 - AddUniqe pSelect : %d"), PSelected.Num());


		for (AActor* NewPawn : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(NewPawn))
			{
				UE_LOG(LogTemp, Warning, TEXT("Unit Selection (ForLoopAtEnd?): %d"), Selected.Num());
				BaseAI->SelectedDecalComp->SetVisibility(true);
			}
			else if (AMainBuilding* MBuilding = Cast<AMainBuilding>(NewPawn))
			{
				UE_LOG(LogTemp, Warning, TEXT("Building Selection (ForLoopAtEnd?): %d"), Selected.Num());
				MBuilding->SelectedDecalComp->SetVisibility(true);
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

void ISelectionInterface::NotHit(TArray<APawn*> Building)
{
	// ReSharper disable once CppExpressionWithoutSideEffects
	for(APawn* PawnSrc : Building)
	{
		if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(PawnSrc))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(false);
		}
	}
}

bool ISelectionInterface::IsUnitSelected(const AActor* BuildingToCheck, const TArray<AActor*>& BuildingArray)
{
	for (const AActor* Actor : BuildingArray)
	{
		if (Actor == BuildingToCheck)
		{
			return true;
		}
	}
	return false;
}

bool ISelectionInterface::isBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck)
{
	for (const APawn* Pawn : BuildingArray)
	{
		if (Pawn == BuildingToCheck)
		{
			return true;
		}
	}
	return false;
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
