// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};



// Types of Buildings
UENUM(BlueprintType)
enum class  EBuildingTypes : uint8
{
	Hall,
	Barracks,
	Trader,
	Invalid,
};


const char* to_string(EBuildingTypes e);


UENUM(BlueprintType)
enum class EUnitTypes : uint8
{
	Worker,
	Military,
	Unknown,
};


class RTS_API ISelectionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Good for Switch Statements Look into it?
	//TEnumAsByte<EBuildingTypes> BuildingType;
	
	
//	TEnumAsByte<EUnitTypes> UnitT;
	
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

	// Returns the type of unit.
	static EUnitTypes GetUnitType(const AActor* Unit);

	//virtual bool IsUnitOftype(EUnitTypes UnitType) const;
	
	// Assigns the type of Unit.
	static UClass* AssignUnitType(const AActor* Unit);
	
	// Check if a specific element is in the array.
	static bool IsBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck);
	
	// Hits the units that are selected
	UFUNCTION()
	virtual void UnitSelection();


	// SingleClick Selection Unit - Deselects Units and Selects New Units
	static void UnitSelection(TArray<AActor*> &Selected, AActor* HitActor);
	// SingleClick Selection Building - Deselects Buildings and Selects New Buildings
	static void BuildingArrayIsEmpty(TArray<AActor*> &Building, AActor* HitPawn);

	static void ChangeElementInBuildingArray(TArray<AActor*> &Building, AActor* HitPawn);
	//void SwapActor(TArray<AActor*> &Selected,TArray<AActor*> &PSelected, AActor* HitActor);
	
	// MultiClick Selection - Stores old units and Selects New Units
	static void MultiUnitSelection(TArray<AActor*> &Selected, AActor* HitActor);

	static void NotHit(TArray<AActor*> &Building);

	bool IsUnitSelected( const AActor* BuildingToCheck, const TArray<AActor*>& BuildingArray);

	bool isBuildingSelected(const TArray<APawn*>& BuildingArray, const APawn* BuildingToCheck);





	
};
