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
	//if (UnitToProduce->GetClass() == AlightInfantry::StaticClass())
	{
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
				GetWorldTimerManager().SetTimer(ProductionTimer, this, &ABarracksBuilding::ProduceUnit, 5.0f,
				                                true);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not enough food to produce unit."));
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("b4e"));
	// Check the type of UnitToProduce
	if (UnitToProduce->IsChildOf(AWorkerDrone::StaticClass()))

	//if (UnitToProduce->GetClass() == AWorkerDrone::StaticClass())
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
		
		ProduceUnitEvent.Broadcast(UnitToProduce, UnitProductionBox->GetComponentLocation());
	}
	else
	{
		// No more units to produce, so stop the timer
		GetWorldTimerManager().ClearTimer(ProductionTimer);
	}
}
