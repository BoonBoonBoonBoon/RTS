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
	
	// Friendly AI 
	TArray<AGenericBaseAI*> AttackingUnits;


	void FindEnemy(AActor* EnemyActor, TArray<AActor*> FriendlyActors); // 1
	
	void ProccessActors(TArray<AActor*> Array); // 2

	TArray<AGenericBaseAI*> ProccessAttackMode(AActor* Units);

	
	TArray<FVector> GetAllLocationsAroundEnemy(FVector enemyLocation, float radius, float stepSize);

	TArray<FVector> GetAllLocationsWithinRadius(FVector center, float radius);

	
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
