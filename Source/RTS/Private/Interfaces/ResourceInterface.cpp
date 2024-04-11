// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ResourceInterface.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerAttributesComponent.h"
#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerDrone.h"
#include "Economy/ResourceTransaction.h"
#include "Resources/FoodResource.h"
#include "Resources/GoldResource.h"
#include "Resources/StoneResource.h"
#include "Resources/WoodResource.h"


// Add default functionality here for any IResourceInterface functions that are not pure virtual.


AActor* IResourceInterface::HandleIdentification(AActor* Resource)
{
	if (Resource->IsA<AWoodResource>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Wood"));
		return Resource;
	}
	else if (Resource->IsA<AStoneResource>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Stone"));
		return Resource;
	}
	else if (Resource->IsA<AGoldResource>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Gold"));
		return Resource;
	}
	else if (Resource->IsA<AFoodResource>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Food"));
		return Resource;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Resource Type!"));
		return nullptr;
	}
}

TArray<FVector> IResourceInterface::CalcGatherPos(AActor* Resources, const TArray<AActor*>& Drones)
{
	// Array Initialization for Gather Positions.
	TArray<FVector> GatherPositions;

	if (!Resource || Drones.IsEmpty())
	{
		return GatherPositions; // Return an empty array if the resource or the drones array is empty.
	}

	float CollisionSphereRadius = 200.0f; // Radius of the collision sphere around the resource.

	int32 TotalDrones = Drones.Num(); // Total number of drones available for gathering.
	float AngleStep = 360.0f / TotalDrones; // Angle step between each drone.

	for (int32 DroneIndex = 0; DroneIndex < TotalDrones; ++DroneIndex) // Loop through each drone.
	{
		float RandomOffset = FMath::RandRange(-AngleStep / 4, AngleStep / 4);
		// Random offset to avoid drones gathering at the same position.
		float Angle = AngleStep * DroneIndex + RandomOffset; // Calculate the angle for the current drone.
		float AngleRadians = FMath::DegreesToRadians(Angle); // Convert the angle to radians.

		FVector Offset = FVector(FMath::Cos(AngleRadians) * CollisionSphereRadius,
		                         FMath::Sin(AngleRadians) * CollisionSphereRadius,
		                         0.0f); // Calculate the offset for the current drone.
		FVector GatherPosition = Resources->GetActorLocation() + Offset;
		// Calculate the gather position for the current drone.

		GatherPositions.Add(GatherPosition); // Add the gather position to the array.
	}
	return GatherPositions; // Return the array of gather positions.
}

void IResourceInterface::TakeResourceObject(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
                                            const FHitResult& Hi)
{
	TArray<AActor*> CollectingActors;
	CollectingActors.Add(OtherActor);

	// Check if the Actor is able to gather resources.
	UWorkerAttributesComponent* AttributesComponent = Cast<UWorkerAttributesComponent>(
		OtherActor->GetComponentByClass(UWorkerAttributesComponent::StaticClass()));
	
		for (AActor* Src : CollectingActors)
		{
			if (Src->IsA(AWorkerDrone::StaticClass()))
			{
				if (AttributesComponent->CanGather() == true)
				{
					// Cast to All Possible Variants
					const EResourceType ResourceTypeInvalid = (SelfActor && SelfActor->IsA<AResourceMain>())
						                                          ? Cast<AResourceMain>(SelfActor)->GetResourceType()
						                                          : EResourceType::Invalid;
					const EResourceType ResourceTypeWood = (SelfActor && SelfActor->IsA<AWoodResource>())
						                                       ? Cast<AWoodResource>(SelfActor)->GetResourceType()
						                                       : EResourceType::Invalid;
					const EResourceType ResourceTypeStone = (SelfActor && SelfActor->IsA<AStoneResource>())
						                                        ? Cast<AStoneResource>(SelfActor)->GetResourceType()
						                                        : EResourceType::Invalid;
					const EResourceType ResourceTypeGold = (SelfActor && SelfActor->IsA<AGoldResource>())
						                                       ? Cast<AGoldResource>(SelfActor)->GetResourceType()
						                                       : EResourceType::Invalid;
					const EResourceType ResourceTypeFood = (SelfActor && SelfActor->IsA<AFoodResource>())
						                                       ? Cast<AFoodResource>(SelfActor)->GetResourceType()
						                                       : EResourceType::Invalid;

					// Creates a new object of the Resource Transaction Class.
					UResourceTransaction* ResourceTransaction = NewObject<UResourceTransaction>();

					if (ResourceTypeInvalid == EResourceType::Invalid)
					{
						UE_LOG(LogTemp, Warning, TEXT("Invalid"));
						ResourceTransaction->TransactionProcess(Cast<AResourceMain>(SelfActor));
					}
					else if (ResourceTypeWood == EResourceType::Wood)
					{
						UE_LOG(LogTemp, Warning, TEXT("Wood"));
						ResourceTransaction->TransactionProcess(Cast<AWoodResource>(SelfActor));
					}
					else if (ResourceTypeStone == EResourceType::Stone)
					{
						UE_LOG(LogTemp, Warning, TEXT("Stone"));
						ResourceTransaction->TransactionProcess(Cast<AStoneResource>(SelfActor));
					}
					else if (ResourceTypeGold == EResourceType::Gold)
					{
						UE_LOG(LogTemp, Warning, TEXT("Gold"));
						ResourceTransaction->TransactionProcess(Cast<AGoldResource>(SelfActor));
					}
					else if (ResourceTypeFood == EResourceType::Food)
					{
						UE_LOG(LogTemp, Warning, TEXT("Food"));
						ResourceTransaction->TransactionProcess(Cast<AFoodResource>(SelfActor));
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Actor Can't Gather Resources."));
				CollectingActors.Remove(Src);
				return;
			}
		}
	}
	// Use transaction class. where in function we tell wood resource to reduce its int, and resource interface to increase its int.
	//Mediator Pattern: Introduce a mediator class that handles communication between classes. Instead of classes communicating directly with each other, they communicate through the mediator, which reduces direct dependencies.



int32 IResourceInterface::GetAmount(int Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Amount: %d"), Amount);
	return {};
}



/*FString IResourceInterface::GetEnumName()
{
	return {};
}

void IResourceInterface::TakeResources(int32 amount)
{
}
#1#*/
// Assign something to the GetType() function when its called, like APawn* Wood = Resource->GetType();

/*EResourceType IResourceInterface::GetType(AActor* Actor)
{
	/*
	 / Assuming you have a property or method to determine the type of the resource
	if (Actor->IsA(EResourceType::Wood)) // Example condition to check if it's a wood resource
	{
		UE_LOG(LogTemp, Warning, TEXT("Wood"));
		return EResourceType::Wood;
	}

	/*if (Actor->IsA(EResourceType::Stone)()) // Example condition to check if it's a stone resource
	{
		UE_LOG(LogTemp, Warning, TEXT("Stone"));
		return EResourceType::Stone;
	}
	if (Actor->IsA(EResourceType::Gold)()) // Example condition to check if it's a metal resource
	{
		UE_LOG(LogTemp, Warning, TEXT("Gold"));
		return EResourceType::Gold;
	}
	if (Actor->IsA(EResourceType::Food)()) // Example condition to check if it's a food resource
	{
		UE_LOG(LogTemp, Warning, TEXT("Food"));
		return EResourceType::Food;
	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Resource Type!"));
		return {};
	//}
}
*/
