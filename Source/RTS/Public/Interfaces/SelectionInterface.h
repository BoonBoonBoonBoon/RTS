// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInterface.generated.h"

// Declare the delegate for the actor can gather.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorCanGatherDelegate, AActor*, GatherActor);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};

// Stores the actor type of possible unit classes. 
UENUM(BlueprintType)
enum class EUnitTypes : uint8
{
	Worker,
	LightInfantry,
	Scout,
	Siege,
	Ranged,
	HeavyInfantry,
	Harasser,
	Transport,
	Invalid,
};

// Stores the possible attributes of a single & or multiple units.
UENUM()
enum class EUnitAttributes
{
	Gather,
	Attack,
	Repair,
	Build,
	Guard,
	Patrol,
	Shoot,
	Transport,
	Search,
	Invalid,
};

// Stores the manipulative elements a unit can contain.
USTRUCT()
struct FUnitStats
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category= "Health")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageDealt;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "UnitType")
	EUnitTypes UnitType;
};

// Types of Buildings
UENUM(BlueprintType)
enum class EBuildingTypes : uint8
{
	Hall,
	Barracks,
	Trader,
	Invalid,
};

const char* to_string(EBuildingTypes e);


class RTS_API ISelectionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	static FOnActorCanGatherDelegate OnActorCanGather;
	
	// Returns the type of building.
	static EBuildingTypes GetBuildingType(const AActor* Building);

	// Assigns the type of building.
	static EBuildingTypes AssignBuildingType(const AActor* Building);

	// Casts the building to a pawn.
	static void CastTo(AActor* Pawn);

	// Selects the building for tasks.
	static void FillArray(TArray<AActor*> Building);

	// Empties the array for building.
	static void EmptyArray(TArray<AActor*> Building);

	// Check if a specific element is in the array.
	static bool IsBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck);

	// Hits the units that are selected
	UFUNCTION()
	virtual void UnitSelection();

	// SingleClick Selection Unit - Deselects Units and Selects New Units
	static void UnitSelection(TArray<AActor*>& Selected, AActor* HitActor);

	// SingleClick Selection Building - Deselects Buildings and Selects New Buildings
	static void BuildingArrayIsEmpty(TArray<AActor*>& Building, AActor* HitPawn);

	// Removes Existing Element in Array and Adds New Element.
	static void ChangeElementInArray(TArray<AActor*>& Array, AActor* HitPawn);

	// MultiClick Selection - Stores old units and Selects New Units
	static void MultiUnitSelection(TArray<AActor*>& Selected, AActor* HitActor);

	static void NotHit(TArray<AActor*>& Array);

	// Returns a specific Unit into a sovereign container.
	static TArray<AActor*> CheckUnitTypeForGathering(TArray<AActor*>& SelectedUnits);

	// Calculates the grid formation positions.
	static TArray<FVector> CalculateGridFormationPositions(FVector TargetLocation, int32 UnitsCount, float Spacing = 300.0f);

	void MoveGroupToLocation(TArray<AActor*> Units, FVector TargetLocation);
	
	static bool CheckValidHit(AActor* HitActor);
	
	// Check if a specific element is in the array.
	static bool IsUnitSelected(const TArray<AActor*>& UnitArray, const AActor* UnitToCheck);

	// Determines the type of unit.
	static void HandleTypes(const TArray<AActor*>& UnitArray, AActor* UnitActor);

	// Pulls the specific Unit ID Type.
	static EUnitTypes GetUnitType(const AActor* UnitActor);

	// Stores the attributes of a specific unit.
	static TMap<EUnitTypes, TArray<EUnitAttributes>> UnitTypeToAttributesMap;

	// Assigns the attributes of a specific unit.
	static TMap<EUnitTypes, TArray<EUnitAttributes>> GetAttributesForunit(EUnitTypes UnitTypes); // chucking errors here


	// Logging Functions.

	static FString EnumToString(EUnitTypes EnumValue);

	static FString EnumToString(EUnitAttributes EnumValue);

	static void LogUnitTypeToAttributesMap(TMap<EUnitTypes, TArray<EUnitAttributes>> AttributesMap);
};
