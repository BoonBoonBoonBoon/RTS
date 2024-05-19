// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BarracksBuilding.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"

ABarracksBuilding::ABarracksBuilding()
{
	//BuildingType = EBuildingTypes::Barracks;

	UnitProductionBox = CreateDefaultSubobject<UBoxComponent>("UnitProductionBox");
	UnitProductionBox->SetupAttachment(BoxComponent);

	//SelectedDecalComp->SetRelativeLocation(FVector(0, 0, 0));
	
	// Set the location of UnitProductionBox
	FVector NewLocation = FVector(70, 0, -40);
	UnitProductionBox->SetRelativeLocation(NewLocation);
	
	DroneToProduce = AWorkerDrone::StaticClass();
	
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

void ABarracksBuilding::ProductionForUnits(float TimeToSpawn)
{
	if (DroneToProduce)
	{
		// Placeholder Value
		if (UserController->UFoodAmount >= 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("more than 1 food "));

			FActorSpawnParameters SpawnParameters;

			AWorkerDrone* WorkerDroneToSpawn = GetWorld()->SpawnActor<AWorkerDrone>(
				DroneToProduce, FVector(0,0,0), UnitProductionBox->GetComponentRotation(),
				SpawnParameters);
			
			//UnitsToProduce.Add(WorkerDroneToSpawn);

			// Start the timer to produce the unit.
			//GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, TimeToSpawn, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not enough food to produce unit."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DroneToProduce is nullptr."));
	}
}


//-------------------
/*
void ABarracksBuilding::ProductionForUnits(float TimeToSpawn)
{
	// Placeholder Value
	if(UserController->UFoodAmount >= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("more than 1 food "));

		AWorkerDrone* WorkerDroneToSpawn = GetWorld()->SpawnActor<AWorkerDrone>();
		UnitsToProduce.Add(WorkerDroneToSpawn);

		// Start the timer to produce the unit.
		GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, TimeToSpawn, false);
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
		UE_LOG(LogTemp, Warning, TEXT("Unit class: %s"), *UnitClass->GetName());
	
		// Define the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// Define the spawn location and rotation
		FVector SpawnLocation = UnitProductionBox->GetComponentLocation(); 
		FRotator SpawnRotation = UnitProductionBox->GetComponentRotation();
		
		UE_LOG(LogTemp, Warning, TEXT("Spawn location: %s"), *SpawnLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Spawn rotation: %s"), *SpawnRotation.ToString());
		
		// Spawn the unit
		//GetWorld()->SpawnActor<AActor>(UnitClass, SpawnLocation, SpawnRotation, SpawnParams);
		AWorkerDrone* WorkerDroneToSpawn = GetWorld()->SpawnActor<AWorkerDrone>(UnitClass, SpawnLocation, SpawnRotation, SpawnParams);
		GLog->Log("Spawned the WorkerDroneToSpawn.");
		
		// Remove the first element from the array
		UnitsToProduce.RemoveAt(0);

		// If there are more units to produce, start the timer again
		if (UnitsToProduce.Num() >= 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Still Units Waiting to be Produced."));
			float TimeToSpawn = 10.0f; 
			GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, TimeToSpawn, false);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ProductionTimer);
		UE_LOG(LogTemp, Warning, TEXT("UnitsToProduce is empty or the first element is nullptr."));
	}
}
*/
