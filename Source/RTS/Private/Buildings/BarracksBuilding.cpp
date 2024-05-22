// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BarracksBuilding.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Elements/Framework/TypedElementQueryBuilder.h"

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

void ABarracksBuilding::ProductionForUnits(TSubclassOf<AGenericBaseAI> UnitToProduce)
{
	if (UnitToProduce->IsChildOf(AlightInfantry::StaticClass()))
	{
		// Check the type of UnitToProduce
		if (UnitToProduce->IsChildOf(AWorkerDrone::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("UnitToProduce is of type WorkerDrone"));

			// Check if there is enough food to produce the unit
			if (UserController->UWoodAmount >= 5 && UserController->UFoodAmount >= 5)
			{
				// Deduct the food cost
				UserController->OnFoodChanged(-5);
				UserController->OnWoodChanged(-5);

				// Add the unit to the production queue
				UnitsForProduction.Enqueue(UnitToProduce);
				UE_LOG(LogTemp, Warning, TEXT("UnitToProduce enqueued: %s"), *UnitToProduce->GetName());

				// Start the production timer if it's not already running
				if (!GetWorldTimerManager().IsTimerActive(ProductionTimer))
				{
					UE_LOG(LogTemp, Warning, TEXT("Set timer"));
					GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, 5.0f, true);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not enough food to produce unit."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UnitToProduce is of an unknown type"));
		}
	}

	// Check the type of UnitToProduce
	if (UnitToProduce->IsChildOf(AWorkerDrone::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitToProduce is of type WorkerDrone"));
		// Check if there is enough food to produce the unit
		if (UserController->UFoodAmount >= 5)
		{
			// Deduct the food cost
			UserController->OnFoodChanged(-5);

			// Add the unit to the production queue
			UnitsForProduction.Enqueue(UnitToProduce);
			UE_LOG(LogTemp, Warning, TEXT("UnitToProduce enqueued: %s"), *UnitToProduce->GetName());

			// Start the production timer if it's not already running
			if (!GetWorldTimerManager().IsTimerActive(ProductionTimer))
			{
				UE_LOG(LogTemp, Warning, TEXT("Set timer"));
				GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, 5.0f, true);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not enough food to produce unit."));
		}
	}
}

void ABarracksBuilding::ProduceUnit()
{
	// Check if there are any units in the queue
	if (!UnitsForProduction.IsEmpty())
	{
		// Dequeue the next unit
		TSubclassOf<AGenericBaseAI> UnitToProduce;
		UnitsForProduction.Dequeue(UnitToProduce);

		// Spawn the unit
		//FActorSpawnParameters SpawnParameters;
		//SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//GetWorld()->SpawnActor<AGenericBaseAI>(UnitToProduce, UnitProductionBox->GetComponentLocation(), UnitProductionBox->GetComponentRotation(), SpawnParameters);

		ProduceUnitEvent.Broadcast(UnitToProduce, UnitProductionBox->GetComponentLocation());
		
	}
	else
	{
		// No more units to produce, so stop the timer
		GetWorldTimerManager().ClearTimer(ProductionTimer);
	}
}



/*
// Placeholder Value
if (UserController->UFoodAmount >= 5)
{
	UE_LOG(LogTemp, Warning, TEXT("Creating Worker Drone"));
	UserController->OnFoodChanged(-5);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	AWorkerDrone* WorkerDroneToSpawn = GetWorld()->SpawnActor<AWorkerDrone>(
		DroneToProduce, UnitProductionBox->GetComponentLocation(), UnitProductionBox->GetComponentRotation(),
		SpawnParameters);

	//UnitsToProduce.Add(WorkerDroneToSpawn);

	// Start the timer to produce the unit.
	//GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, TimeToSpawn, false);
}
else
{
	UE_LOG(LogTemp, Warning, TEXT("Not enough food to produce unit."));
}
*/




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
