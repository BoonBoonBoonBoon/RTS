// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AGenericController : public AAIController
{
	GENERATED_BODY()

public:

	AGenericController(FObjectInitializer const& ObjectInitializer);

	// When pawn is Possessed by controller, initialize the blackboard assets.
	virtual void OnPossess(APawn* InPawn) override;

	// Run behaviour tree immediately
	virtual void BeginPlay() override;
	
	// Sight Perception
	void SetupPer();

	void MoveToDes(FVector& Destination);
};
