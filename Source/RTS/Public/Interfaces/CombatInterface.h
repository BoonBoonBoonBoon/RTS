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

	/*
	virtual FVector FoundEnemyLocation() = 0;
	virtual bool MoveToEnemy() = 0;
	virtual void AttackEnemy() = 0;
	*/

	
	TArray<FVector> CalculateSurroundingPositions(FVector EnemyLocation, int32 UnitsCount, float Radius);

	TArray<FVector> CalculateRandomPositions(FVector EnemyLocation, int32 UnitsCount, float Radius);
	
	TArray<AGenericBaseAI*> AttackingUnits;
	
	bool IsLocationOccupied(FVector Location, TArray<AActor*> FriendlyActors, float Radius);
	
	///virtual void CustomTick(float DeltaTime);
	
	void MoveToEnemy(AActor* EnemyActor,TArray<AActor*> FriendlyActors);

	void SurroundEnemy(AActor* EnemyActor, TArray<AGenericBaseAI*> FriendlyActors);
	
	TArray<AGenericBaseAI*> ProccessAttackMode(TArray<AActor*> Units);
	
	bool bFoundEnemyLocation = false;
	
};
