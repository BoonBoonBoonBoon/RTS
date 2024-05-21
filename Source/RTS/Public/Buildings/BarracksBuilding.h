// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserController.h"
#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/lightInfantry.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Buildings/MainBuilding.h"
#include "BarracksBuilding.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProudceUnitEvent, TSubclassOf<AGenericBaseAI>, UnitToProduce, FVector, SpawnLocation);

/**
 * 
 */
UCLASS()
class RTS_API ABarracksBuilding : public AMainBuilding
{
	GENERATED_BODY()

public:
	ABarracksBuilding();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Production")
	UBoxComponent* UnitProductionBox;
	
	// Reference to the User Controller.
	AUserController* UserController;
	
	FTimerHandle ProductionTimer;

	UPROPERTY(BlueprintAssignable)
	FProudceUnitEvent ProduceUnitEvent;
	
	// Add a queue to hold the units waiting to be produced
	TQueue<TSubclassOf<AGenericBaseAI>> UnitsForProduction;
	
	UFUNCTION(BlueprintCallable)
	void ProductionForUnits(TSubclassOf<AGenericBaseAI> UnitToProduce);
	void ProduceUnit();

	//void ProduceUnit();

	UPROPERTY(EditDefaultsOnly, Category = "Unit Production")
	TSubclassOf<AGenericBaseAI> DroneToProduce;

	UPROPERTY(EditDefaultsOnly, Category = "Unit Production")
	TSubclassOf<AlightInfantry> lightInfantryToProduce;

	UPROPERTY(EditDefaultsOnly, Category = "Unit Production")
	TSubclassOf<AWorkerDrone> WorkerDroneToProduce;

	
	
	// Array that stores the current units that are intended to be produced.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWorkerDrone*> UnitsToProduce;

	// Check to see if the building is currently producing a unit.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsProducingUnit = false;
	
};
