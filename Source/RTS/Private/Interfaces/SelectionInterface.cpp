// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SelectionInterface.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/lightInfantry.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Buildings/BarracksBuilding.h"
#include "Buildings/MarketplaceBuilding.h"
#include "Components/DecalComponent.h"

// Assign the Signature to the Delegate.
FOnActorCanGatherDelegate ISelectionInterface::OnActorCanGather;

class IUnitInterface;
class AGenericBaseAI;
TMap<EUnitTypes, TArray<EUnitAttributes>> ISelectionInterface::UnitTypeToAttributesMap;

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
		if (const AMarketplaceBuilding* TBuilding = Cast<AMarketplaceBuilding>(Building))
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
		if (Cast<AMarketplaceBuilding>(Building))
		{
			UE_LOG(LogTemp, Warning, TEXT("Building type assigned: Trader"));
			return EBuildingTypes::Trader;
		}
		if (Cast<AMainBuilding>(Building))
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
	}
	else
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
	if (Array.Num() > 0)
	{
		for (AActor* Actor : Array)
		{
			if (const AMainBuilding* MBuilding = Cast<AMainBuilding>(Actor))
			{
				MBuilding->SelectedDecalComp->SetVisibility(false);
				Array.Empty();

				Array.AddUnique(HitPawn);
				for (AActor* SrcP : Array)
				{
					if (const AMainBuilding* NewBuilding = Cast<AMainBuilding>(SrcP))
					{
						NewBuilding->SelectedDecalComp->SetVisibility(true);
					}
				}
			}
			else if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Actor))
			{
				BaseAI->SelectedDecalComp->SetVisibility(false);
				Array.Empty();

				Array.AddUnique(HitPawn);
				for (AActor* Src : Array)
				{
					if (const AGenericBaseAI* NewBaseAI = Cast<AGenericBaseAI>(Src))
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
	if (Cast<AGenericBaseAI>(HitActor))
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

void ISelectionInterface::NotHit(TArray<AActor*>& Array)
{
	// Loops through all the elements and turns vis off

	for (AActor* PawnSrc : Array)
	{
		if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(PawnSrc))
		{
			MainBuilding->SelectedDecalComp->SetVisibility(false);
			Array.Empty();
		}
		else if (const AGenericBaseAI* AI = Cast<AGenericBaseAI>(PawnSrc))
		{
			AI->SelectedDecalComp->SetVisibility(false);
			Array.Empty();
		}
	}
}

TArray<AActor*> ISelectionInterface::CheckUnitTypeForGathering(TArray<AActor*>& SelectedUnits)
{
	TArray<AActor*> WorkerDrones;
	
	// Check if the selected unit is a worker drone.
	for (AActor* Src : SelectedUnits)
	{
		if (AWorkerDrone* Worker = Cast<AWorkerDrone>(Src))
		{
			WorkerDrones.AddUnique(Worker);
		}
	}
	return WorkerDrones;
}

TArray<FVector> ISelectionInterface::CalculateGridFormationPositions(FVector TargetLocation, int32 UnitsCount,
	float Spacing)
{
	TArray<FVector> Positions; // Array to store the calculated positions
	
	/* Calculate the square root of the number, then truncate to an integer.
	 * Giving the number of rows. I.e. if 2.5, it will be 2. */
	int32 Rows = FMath::CeilToInt(FMath::Sqrt(float(UnitsCount))); // Calculate the number of rows
	int32 Columns = FMath::CeilToInt(float(UnitsCount) / Rows); // Calculate the number of columns

	// Needs to be in the center, Divide it to be in middle of row, then column with spacing in between.
	FVector StartPosition = TargetLocation - FVector(Rows / 2.0f * Spacing, Columns / 2.0f * Spacing, 0.0f); 

	// iterate through each *row (i) and *column (j) of the grid.
	for (int32 i = 0; i < Rows; ++i)
	{
		for (int32 j = 0; j < Columns; ++j)
		{
			if (i * Columns + j >= UnitsCount) break; // Stop if we've placed all units

			FVector Position = StartPosition + FVector(i * Spacing, j * Spacing, 0.0f);
			Positions.Add(Position);
		}
	}
	
	return Positions;
}

void ISelectionInterface::MoveGroupToLocation(TArray<AActor*> Units, FVector TargetLocation)
{
	TArray<FVector> FormationPositions = CalculateGridFormationPositions(TargetLocation, Units.Num());

	for (int32 i = 0; i < Units.Num(); ++i)
	{
		AActor* Unit = Units[i];
		FVector AssignedPositions = FormationPositions[i];

		int32 LoopBound = FMath::Min(Units.Num(), FormationPositions.Num());
		for (int32 INT32 = 0; INT32 < LoopBound; ++INT32)
		{
			if (const AGenericBaseAI* GenAI = Cast<AGenericBaseAI>(Unit))
			{
				if (GenAI->GetController())
				{
					GenAI->LocationToMove = AssignedPositions;
					GenAI->ValidHit = true;
				}
			}
		}

		/*for (int32 l = 0; l < FormationPositions.Num(); ++l)
		{
			FVector Position = FormationPositions[l];
			UE_LOG(LogTemp, Log, TEXT("Unit %d: Position: %s"), l, *Position.ToString());
		}
	}*/
}


bool ISelectionInterface::CheckValidHit(AActor* HitActor)
{
	// Change
	return {};
}

bool ISelectionInterface::IsUnitSelected(const TArray<AActor*>& UnitArray, const AActor* UnitToCheck)
{
	return UnitArray.Contains(UnitToCheck);
}

void ISelectionInterface::HandleTypes(const TArray<AActor*>& UnitArray, AActor* UnitActor)
{
	// Checks validity of the unit.
	if (IsUnitSelected(UnitArray, UnitActor))
	{
		// Identify The Unit Type
		const EUnitTypes UnitType = GetUnitType(UnitActor);

		// Identify the attributes of the unit.
		const TMap<EUnitTypes, TArray<EUnitAttributes>> UnitAttributes = GetAttributesForunit(UnitType);

		// Logs The attributes of the unit.
		LogUnitTypeToAttributesMap(UnitAttributes);


		if (UnitTypeToAttributesMap.Contains(UnitType)) // Check if the TMap Contains a valid unit type.
		{
			// Then assign the attributes of the unit to the new Attribute TArray. If the unit has the Gather attribute, then it can gather resources.
			if (TArray<EUnitAttributes> Att = UnitTypeToAttributesMap[UnitType]; Att.Contains(EUnitAttributes::Gather))
			{
				// Find the component of the current incoming unit object.
				if (UWorkerAttributesComponent* ActorAttributes = UnitActor->FindComponentByClass<
					UWorkerAttributesComponent>())
				{
					ActorAttributes->SetCanGather(true);
					UE_LOG(LogTemp, Warning, TEXT("Can Gather Resources"));
				
				}
			}
			else if (UActorAttributesComponent* ActorAtt = UnitActor->FindComponentByClass<UActorAttributesComponent>())
			{
				ActorAtt->SetCanGather(false);
			}
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
			return EUnitTypes::Worker;
		}
		if (Cast<AlightInfantry>(UnitActor))
		{
			return EUnitTypes::LightInfantry;
		}
	}
	return EUnitTypes::Invalid;
}

TMap<EUnitTypes, TArray<EUnitAttributes>> ISelectionInterface::GetAttributesForunit(EUnitTypes UnitTypes)
{
	if (UnitTypes == EUnitTypes::Worker)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unit Type: Worker"));
		// Map of unit types to attributes.
		UnitTypeToAttributesMap = {
			{EUnitTypes::Worker, {EUnitAttributes::Gather, EUnitAttributes::Repair, EUnitAttributes::Build}},
		};
		return UnitTypeToAttributesMap;
	}
	if (UnitTypes == EUnitTypes::LightInfantry)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unit Type: Light Infantry"));
		// Map of unit types to attributes.
		UnitTypeToAttributesMap = {
			{EUnitTypes::LightInfantry, {EUnitAttributes::Attack, EUnitAttributes::Guard, EUnitAttributes::Patrol}}
		};
		return UnitTypeToAttributesMap;
	}
	UE_LOG(LogTemp, Warning, TEXT("Invalid Unit Type"));
	return {};
}


// Function to convert EUnitTypes enum to string
FString ISelectionInterface::EnumToString(EUnitTypes EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EUnitTypes"), true);
	if (!EnumPtr)
	{
		return FString("Invalid");
	}

	return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
}

// Function to convert EUnitAttributes enum to string
FString ISelectionInterface::EnumToString(EUnitAttributes EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EUnitAttributes"), true);
	if (!EnumPtr)
	{
		return FString("Invalid");
	}

	return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
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
