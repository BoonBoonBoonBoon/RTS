// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserController.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Buildings/MainBuilding.h"
#include "BarracksBuilding.generated.h"


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
	
	// Function used to produce units.
	//UFUNCTION(BlueprintCallable)
	//void ProductionForUnits(AActor* UnitToSpawn, int32 AmountToSpawn, float TimeToSpawn);
	
	UFUNCTION(BlueprintCallable)
	void ProductionForUnits( float TimeToSpawn);

	void ProduceUnit();

	UPROPERTY(EditDefaultsOnly, Category = "Unit Production")
	TSubclassOf<AWorkerDrone> DroneToProduce;

	
	// Array that stores the current units that are intended to be produced.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWorkerDrone*> UnitsToProduce;

	// Check to see if the building is currently producing a unit.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsProducingUnit = false;
	
};
