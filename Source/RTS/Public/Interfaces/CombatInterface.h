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

	void FindEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors);

	TArray<AGenericBaseAI*> ProccessAttackMode(TArray<AActor*> Units);
	bool bUnitFound;
	bool IsLocationOccupied(FVector Location, TArray<AGenericBaseAI*> FriendlyActors, float Radius);
	void MoveUnitsToSeparateLocations(TArray<AGenericBaseAI*> FriendlyActors, FVector TargetLocation);
	float MeleeAttackRange = 150.f;
	float RangedAttackRange = 1000.f;
	FVector CurrentEnemy = FVector::ZeroVector;
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
