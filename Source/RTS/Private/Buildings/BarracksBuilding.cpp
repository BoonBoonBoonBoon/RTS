// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BarracksBuilding.h"

#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Components/BoxComponent.h"

ABarracksBuilding::ABarracksBuilding()
{
	//BuildingType = EBuildingTypes::Barracks;

	UnitProductionBox = CreateDefaultSubobject<UBoxComponent>("UnitProductionBox");
	UnitProductionBox->SetupAttachment(RootComponent);
	
	// Set the location of UnitProductionBox
	FVector NewLocation = FVector(70, 0, -40);
	UnitProductionBox->SetRelativeLocation(NewLocation);
	
	
	Tags.Add("Barracks");
	
}

void ABarracksBuilding::BeginPlay()
{
	Super::BeginPlay();

	// Initialize UserController
	UserController = Cast<AUserController>(GetWorld()->GetFirstPlayerController());
	if (!UserController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UserController not found."));
	}
}


// Add the selected unit into a production array and set production to true. we then set a timer to produce the specific unit.
/*void ABarracksBuilding::ProductionForUnits(AActor* UnitToSpawn, int32 AmountToSpawn, float TimeToSpawn)
{
	// Placeholder Value
	if(UserController->UFoodAmount >= 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("more than 5 food "));

		
		// Cast the UnitToSpawn to AWorkerDrone
		if(AWorkerDrone* WorkerDroneToSpawn = Cast<AWorkerDrone>(UnitToSpawn))
		{
			UE_LOG(LogTemp, Warning, TEXT("Worker Drone"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not a Worker Drone"));
		}

		
		// Set the building to be producing a unit.
		//bIsProducingUnit = true;

		// Add the unit to the array.
		//UnitsToProduce.Add(UnitToSpawn);

		// Start the timer to produce the unit.
		//GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, TimeToSpawn, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough food to produce unit."));
	}
}*/

void ABarracksBuilding::ProductionForUnits(float TimeToSpawn)
{
	// Placeholder Value
	if(UserController->UFoodAmount >= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("more than 1 food "));

		AWorkerDrone* WorkerDroneToSpawn;

		UnitsToProduce.Add(WorkerDroneToSpawn);
		
		// Cast the UnitToSpawn to AWorkerDrone
		/*
		if(AWorkerDrone* WorkerDroneToSpawn = Cast<AWorkerDrone>(UnitToSpawn))
		{
			UE_LOG(LogTemp, Warning, TEXT("Worker Drone"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not a Worker Drone"));
		}
		*/

		
		// Set the building to be producing a unit.
		//bIsProducingUnit = true;

		// Add the unit to the array.
		//UnitsToProduce.Add(UnitToSpawn);

		// Start the timer to produce the unit.
		GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, TimeToSpawn, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough food to produce unit."));
	}
}

void ABarracksBuilding::ProduceUnit()
{
	if (UnitsToProduce.Num() > 0 && UnitsToProduce[0] != nullptr)
	{
		// Get the class of the unit to spawn
		UClass* UnitClass = UnitsToProduce[0]->GetClass();

		// Print the name of the unit to spawn
		FString UnitName = UnitClass->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Spawning unit: %s"), *UnitName);

		// Define the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Define the spawn location and rotation
		FVector SpawnLocation = GetActorLocation(); // Change to collision box 
		FRotator SpawnRotation = GetActorRotation();

		// Spawn the unit
		GetWorld()->SpawnActor<AWorkerDrone>(UnitClass, SpawnLocation, SpawnRotation, SpawnParams);

		// Remove the first element from the array
		UnitsToProduce.RemoveAt(0);

		// If there are more units to produce, start the timer again
		if (UnitsToProduce.Num() > 0)
		{
			float TimeToSpawn = 10.0f; 
			GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, TimeToSpawn, true);
		} else
		{
			GetWorldTimerManager().ClearTimer(ProductionTimer);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ProductionTimer);
		UE_LOG(LogTemp, Warning, TEXT("UnitsToProduce is empty or the first element is nullptr."));
	}
}


