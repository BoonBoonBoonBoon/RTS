// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericController.generated.h"

class AGenericBaseAI;
/**
 * 
 */
UCLASS()
class RTS_API AGenericController : public AAIController
{
	GENERATED_BODY()

public:

	mutable FVector MoveLoc;
	mutable bool CheckValid;
	void MovePawn();

	bool bIsPatrolling = false;
	FVector PatrolPointA;
	FVector PatrolPointB;
	bool FirstMove = true;
	
	// The Current Patrol Point the AI is moving to.
	TArray<AGenericBaseAI*> PatrolUnits;

	// Checks if the AI is at the patrol point.
	bool bIsAtPointA = false;
	bool bIsAtPointB = false;
	
	// The Current Patrol Point the AI is moving to.
	void PatrolLoc();

	
	FVector* DestLoc;

	virtual void Tick(float DeltaSeconds) override;
	
	AGenericController(FObjectInitializer const& ObjectInitializer);

	// When pawn is Possessed by controller, initialize the blackboard assets.
	virtual void OnPossess(APawn* InPawn) override;

	// Run behaviour tree immediately
	virtual void BeginPlay() override;
	
	// Sight Perception
	void SetupPer();

	void MoveToDes(FVector& Destination);
};
