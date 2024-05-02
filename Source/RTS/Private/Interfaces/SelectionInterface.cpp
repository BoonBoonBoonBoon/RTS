// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SelectionInterface.h"

#include "UserController.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/lightInfantry.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Buildings/BarracksBuilding.h"
#include "Buildings/BuildingController.h"
#include "Buildings/MarketplaceBuilding.h"
#include "Components/DecalComponent.h"
#include "Widets/MarketPlaceWidget.h"

// Assign the Signature to the Delegate.
FOnActorCanGatherDelegate ISelectionInterface::OnActorCanGather;

class IUnitInterface;
class AGenericBaseAI;
TMap<EUnitTypes, TArray<EUnitAttributes>> ISelectionInterface::UnitTypeToAttributesMap;
//TMap<EUnitTypes, FUnitData> ISelectionInterface::UnitTypeToDataMap;

/**
 * Function to convert EBuildingTypes enum to string
 * @param e - EBuildingTypes enum value
 * @return string representation of the enum value
 */
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


void ISelectionInterface::UnitSelection()
{
}


/**
 * Function to handle unit selection with a given array of selected actors and a hit actor
 * @param Selected - TArray of AActor pointers
 * @param HitActor - AActor pointer
 */
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

/**
 * Function to handle building array when it is empty
 * @param Building - TArray of AActor pointers
 * @param HitPawn - AActor pointer
 */
void ISelectionInterface::BuildingArrayIsEmpty(TArray<AActor*>& Building, AActor* HitPawn)
{
	if (Building.IsEmpty())
	{
		Building.AddUnique(HitPawn);
		for (AActor* SrcP : Building)
		{
			if (AMainBuilding* MBuilding = Cast<AMainBuilding>(SrcP))
			{
				//AActor* Current = Building[0];
				EBuildingTypes CurrentBuilding = GetBuildingType(MBuilding);
				AddBuildingWidget(CurrentBuilding, MBuilding);
			}
		}
	}
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

/**
 * Function to get the building type of a given actor
 * @param Building - AActor pointer
 * @return EBuildingTypes enum value representing the building type
 */
EBuildingTypes ISelectionInterface::GetBuildingType(const AActor* Building)
{
	if (Building)
	{
		if (Cast<ABarracksBuilding>(Building))
		{
			return EBuildingTypes::Barracks;
		}
		if (Cast<AMarketplaceBuilding>(Building))
		{
			return EBuildingTypes::Trader;
		}
	}
	return {};
}

void ISelectionInterface::AddBuildingWidget(EBuildingTypes CurrentBuilding, AActor* ActorToWidget)
{
	// Cast ActorToWidget to AMainBuilding
	if (AMainBuilding* MainBuilding = Cast<AMainBuilding>(ActorToWidget))
	{
		if(CurrentBuilding == EBuildingTypes::Barracks)
		{
			UE_LOG(LogTemp, Warning, TEXT("Barracks Selected"));
			//MainBuilding->OpenBarracks(MainBuilding->bOpenBarracks);
			MainBuilding->bOpenMarketPlace = false;
			MainBuilding->bOpenBarracks = true;
		}
		else if(CurrentBuilding == EBuildingTypes::Trader)
		{
			MainBuilding->bOpenBarracks = false;
			MainBuilding->bOpenMarketPlace = true;
			UE_LOG(LogTemp, Warning, TEXT("Trader Selected"));
			
		}
	}
}

/**
 * Function to change an element in an array with a given hit pawn
 * @param Array - TArray of AActor pointers
 * @param HitPawn - AActor pointer
 */
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
						EBuildingTypes CurrentBuilding = GetBuildingType(NewBuilding);
						AddBuildingWidget(CurrentBuilding, SrcP);
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

/**
 * Function to handle multi unit selection with a given array of selected actors and a hit actor
 * @param Selected - TArray of AActor pointers
 * @param HitActor - AActor pointer
 */
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

/**
 * Function to handle when a hit is not made
 * @param Array - TArray of AActor pointers
 */
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

/**
 * Function to check unit type for gathering
 * @param SelectedUnits - TArray of AActor pointers
 * @return TArray of AActor pointers that are worker drones
 */
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

/**
 * Function to calculate grid formation positions
 * @param TargetLocation - FVector representing the target location
 * @param UnitsCount - int32 representing the number of units
 * @param Spacing - float representing the spacing between units
 * @return TArray of FVector representing the calculated positions
 */
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

/**
 * Moves a group of units to a specified location.
 * @param Units - An array of actors representing the units to be moved.
 * @param TargetLocation - The target location to move the units to.
 */
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
	}
}

/**
 * Checks if a hit is valid.
 * @param HitActor - The actor that was hit.
 * @return A boolean indicating whether the hit is valid.
 */
bool ISelectionInterface::CheckValidHit(AActor* HitActor)
{
	// Change
	return {};
}

/**
 * Checks if a unit is selected.
 * @param UnitArray - An array of actors representing the selected units.
 * @param UnitToCheck - The unit to check.
 * @return A boolean indicating whether the unit is selected.
 */
bool ISelectionInterface::IsUnitSelected(const TArray<AActor*>& UnitArray, const AActor* UnitToCheck)
{
	return UnitArray.Contains(UnitToCheck);
}

/**
 * Handles the types of units.
 * @param UnitArray - An array of actors representing the units.
 * @param UnitActor - The actor representing the unit.
 */
void ISelectionInterface::HandleTypes(const TArray<AActor*>& UnitArray, AActor* UnitActor)
{
	// Checks validity of the unit.
	if (IsUnitSelected(UnitArray, UnitActor))
	{
		if (auto GenActor = Cast<AGenericBaseAI>(UnitActor))
		{
			if(GenActor->UnitDataMap.Contains(GenActor->UnitType))
			{
				// Then assign the attributes of the unit to the new Attribute TArray. If the unit has the Gather attribute, then it can gather resources.
				TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes;
				if (Att.Num() > 0)
				{
					// We then Check the Specific Attributes of the Units To See what they can do
					if(Att.Contains(EUnitAttributes::Gather))
					{
						// Find the component of the current incoming unit object.
						if (UWorkerAttributesComponent* ActorAttributes = GenActor->FindComponentByClass<UWorkerAttributesComponent>())
						{
							ActorAttributes->SetCanGather(true);
						}
					}
					else if(Att.Contains(EUnitAttributes::Attack)) 
					{
						TArray<AActor*> IncAtkUnits;
						
						for (AActor* src : UnitArray)
						{
							IncAtkUnits.AddUnique(src);
							if(ICombatInterface* CombatInterface = GenActor->CombatInterface)
							{
								CombatInterface->ProccessActors(IncAtkUnits);
							}
						}
					}
				} 
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Element Is Not in the Array."));
	}
}

/**
 * Gets the type of a unit.
 * @param UnitActor - The actor representing the unit.
 * @return The type of the unit.
 */
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

/**
 * Gets the attributes for a unit.
 * @param UnitTypes - The type of the unit.
 * @return A map of unit types to attributes.
 */
TMap<EUnitTypes, TArray<EUnitAttributes>> ISelectionInterface::GetAttributesForUnit(EUnitTypes UnitTypes)
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

/**
 * Gets the data for a unit.
 * @param UnitTypes - The type of the unit.
 * @return The data for the unit.
 */
FUnitData ISelectionInterface::GetUnitDataForUnit(EUnitTypes UnitTypes)
{
	// Ensure the map is populated with data for each unit type.
	if (UnitTypes == EUnitTypes::Worker)
	{
		FUnitData WorkerData; 
		WorkerData.Attributes = {
			EUnitAttributes::Gather, EUnitAttributes::Repair, EUnitAttributes::Build
		}; // Worker Attributes
		WorkerData.UnitStats = {100.0f, 0.0f, 100.0f, 100.0f, 0.0f, false, 0.0f, 0.0f}; // Worker Stats
		return WorkerData;
	}
	
	if (UnitTypes == EUnitTypes::LightInfantry)
	{
		FUnitData LightInfantryData;
		LightInfantryData.Attributes = {EUnitAttributes::Attack, EUnitAttributes::Guard, EUnitAttributes::Patrol};
		// Light Infantry Attributes
		LightInfantryData.UnitStats = {100.0f, 0.0f, 100.0f, 100.0f, 10.0f, false, 200.0f, 2.0f}; // Light Infantry Stats
		return LightInfantryData;
		
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Unit Type"));
		
		// Return an empty FUnitData for invalid or unhandled unit types
		return FUnitData();
	}
}

/**
 * Gets the data for a unit.
 * @param UnitTypes - The type of the unit.
 * @return The data for the unit.
 */
void ISelectionInterface::LogUnitTypeToDataMap(const TMap<EUnitTypes, FUnitData>& DataMap)
{
	// Iterate over each key-value pair in the map
	for (const auto& Pair : DataMap)
	{
		// Convert the key (Unit Type) to string
		FString UnitTypeString = EnumToString(Pair.Key);

		// Start building the string for the value (Unit Data)
		FString DataString = TEXT("Attributes: [");
        
		// Append each attribute to the string
		for (const EUnitAttributes& Attribute : Pair.Value.Attributes)
		{
			DataString += EnumToString(Attribute) + TEXT(", ");
		}
		// Remove the trailing comma and space if there are any attributes
		if (Pair.Value.Attributes.Num() > 0)
		{
			DataString.RemoveAt(DataString.Len() - 2);
		}
		DataString += TEXT("], Stats: {");

		// Append each stat to the string
		DataString += FString::Printf(TEXT("Health: %.1f, "), Pair.Value.UnitStats.Health);
		DataString += FString::Printf(TEXT("HealthRegeneration: %.1f, "), Pair.Value.UnitStats.HealthRegeneration);
		DataString += FString::Printf(TEXT("Speed: %.1f, "), Pair.Value.UnitStats.Speed);
		DataString += FString::Printf(TEXT("GroupSpeed: %.1f, "), Pair.Value.UnitStats.GroupSpeed);
		DataString += FString::Printf(TEXT("DamageDealt: %.1f, "), Pair.Value.UnitStats.DamageDealt);
		DataString += FString::Printf(TEXT("AttackRange: %.1f, "), Pair.Value.UnitStats.AttackRange);
		DataString += FString::Printf(TEXT("AttackSpeed: %.1f"), Pair.Value.UnitStats.AttackSpeed);

		DataString += TEXT("}");

		// Log the key-value pair
		UE_LOG(LogTemp, Log, TEXT("%s: %s"), *UnitTypeString, *DataString);
	}
}

/**
 * @brief Processes the given units and returns those that can patrol.
 *
 * This function iterates over the given array of units, checks if each unit has the "Patrol" attribute,
 * and if so, adds it to a new array. This new array, containing only the units that can patrol, is then returned.
 *
 * @param Units An array of actors representing the units to be processed.
 * @return An array of GenericBaseAI pointers representing the units that can patrol.
 */
TArray<AGenericBaseAI*> ISelectionInterface::ProccessPatrolMode(TArray<AActor*> Units)
{
	// Temp array to store the units that can patrol.
	TArray<AGenericBaseAI*> PatrolUnits;

	for (AActor* Src : Units)
	{
		if (auto GenActor = Cast<AGenericBaseAI>(Src))
		{
			if (GenActor->UnitDataMap.Contains(GenActor->UnitType))
			{
				TArray<EUnitAttributes> Att = GenActor->UnitDataMap[GenActor->UnitType].Attributes;

				// We then Check the Specific Attributes of the Units To See what they can do
				if (Att.Contains(EUnitAttributes::Patrol))
				{
					PatrolUnits.AddUnique(GenActor);
				}
			}
		}
	}
	return PatrolUnits;
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



	// ----- Building Stuff -----




/**
 * Function to assign a building type to a given actor
 * @param Building - AActor pointer
 * @return EBuildingTypes enum value representing the assigned building type
 */


/**
 * Function to cast a given pawn to AMainBuilding and set visibility of its SelectedDecalComp to false
 * @param Pawn - AActor pointer
 */
/*void ISelectionInterface::CastTo(AActor* Pawn)
{
	if (const AMainBuilding* MainBuilding = Cast<AMainBuilding>(Pawn))
	{
		MainBuilding->SelectedDecalComp->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Array Wiped - Buildings"));
	}
}*/

/**
 * Function to add a given building to an array and set visibility of its SelectedDecalComp to true
 * @param Building - TArray of AActor pointers
 */
/*void ISelectionInterface::FillArray(TArray<AActor*> Building)
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
}*/

/**
 * Function to remove a given building from an array and set visibility of its SelectedDecalComp to false
 * @param Building - TArray of AActor pointers
 */
/*void ISelectionInterface::EmptyArray(TArray<AActor*> Building)
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
}*/

/**
 * Function to check if a given building is in an array
 * @param BuildingArray - TArray of APawn pointers
 * @param BuildingToCheck - APawn pointer
 * @return true if the building is in the array, false otherwise
 */
/*bool ISelectionInterface::IsBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck)
{
	return BuildingArray.Contains(BuildingToCheck);
}*/