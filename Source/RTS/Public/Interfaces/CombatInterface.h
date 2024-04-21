// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class AGenericBaseAI;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

//	virtual void CombatTick(float DeltaTime);

	// Enemy Detection -----
	
	/*bool EnemyFound = false;
	
	FVector EnemyLocation;
	TArray<AActor*> EnemyActors;*/
	
	// ---------------------

	// Friendly AI -----
	TArray<AGenericBaseAI*> AttackingUnits;
	// -----------------


	TArray<FVector> GetAllLocationsAroundEnemy(FVector enemyLocation, float radius, float stepSize);

	TArray<FVector> GetAllLocationsWithinRadius(FVector center, float radius);

	/**
 * @brief Function to find an enemy actor and initiate the attack process.
 * It finds all friendly actors that can attack and initiates the attack process.
 * If there are friendly actors that can attack, it iterates over them and,
 * for each one, it gets its AI controller and moves it to a location.
 * Finally, it sets the current enemy to the provided enemy actor and sets the EnemyFound flag to true.
 * @param EnemyActor - The enemy actor to find.
 * @param FriendlyActors - The array of friendly actors.
 */
	void FindEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors);

	/**
 * @brief Function to process a given array of units and return those that can attack.
 * It iterates over the given array of units. For each unit, it attempts to cast it to an `AGenericBaseAI`.
 * If the cast is successful and the unit's type is in its `UnitDataMap`, it checks if the unit has the `Attack` attribute.
 * If the unit has the `Attack` attribute, it is added to the `UnitsCanAttack` array.
 * The function returns the `UnitsCanAttack` array, which contains all units from the input array that can attack.
 * @param Units - The array of units to process.
 * @return TArray<AGenericBaseAI*> - The array of units that can attack.
 */
	TArray<AGenericBaseAI*> ProccessAttackMode(AActor* Units);

	
	void ProccessActors(TArray<AActor*> Array);

	bool bUnitFound;
	bool IsLocationOccupied(FVector Location, TArray<AGenericBaseAI*> FriendlyActors, float Radius);
	void MoveUnitsToSeparateLocations(TArray<AGenericBaseAI*> FriendlyActors, FVector TargetLocation);
	float MeleeAttackRange = 150.f;
	float RangedAttackRange = 1000.f;
	FVector CurrentEnemy = {};
	FVector AttackLocation;
	TArray<FVector> AssignedLocations;
	FTimerHandle AttackTimerHandle;
	//void InitiateCombat(bool bIsAttacking, AGenericBaseAI* Unit);
	virtual void AttackEnemy();
	float TimeValue = 2.f ; // Represents a time value
	FVector UpdateEnemyLocation();

	FVector FindAttackLocation(AGenericBaseAI* FriendlyActor);

	void MoveToAttackLocation(AGenericBaseAI* FriendlyActor, FVector AttackLocation);

	TArray<FVector> SurroundingPositions;
};
