// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ResourceInterface.h"

#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "Economy/ResourceTransaction.h"
#include "Interfaces/SelectionInterface.h"
#include "Resources/FoodResource.h"
#include "Resources/GoldResource.h"
#include "Resources/StoneResource.h"
#include "Resources/WoodResource.h"


// Add default functionality here for any IResourceInterface functions that are not pure virtual.


IResourceInterface::IResourceInterface()
{
	//ISelectionInterface::OnActorCanGather.AddDynamic(this, &IResourceInterface::HandleActorCanGatherDelegate);
}

void IResourceInterface::HandleActorCanGatherDelegate(AActor* Actor)
{
	// Store GatherActor or mark it as able to gather resources
	// This could involve adding it to a list or setting a flag on the actor
	//TakeResourceObject(nullptr, Actor, FVector::ZeroVector, FHitResult());
}

AActor* IResourceInterface::HandleIdentification(AActor* Resource)
{
	if(Resource->IsA<AWoodResource>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Wood"));
		return Resource;
	}
	else if(Resource->IsA<AStoneResource>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Stone"));
		return Resource;
	}
	else if(Resource->IsA<AGoldResource>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Gold"));
		return Resource;
	}
	else if(Resource->IsA<AFoodResource>())
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

void IResourceInterface::TakeResourceObject(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
                                            const FHitResult& Hi)
{
	// Check if the Actor is able to gather resources.
	UActorAttributesComponent* AttributesComponent = Cast<UActorAttributesComponent>(
		OtherActor->GetComponentByClass(UActorAttributesComponent::StaticClass()));
	if (AttributesComponent->CanGather())
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

		// Use transaction class. where in function we tell wood resource to reduce its int, and resource interface to increase its int.
		//Mediator Pattern: Introduce a mediator class that handles communication between classes. Instead of classes communicating directly with each other, they communicate through the mediator, which reduces direct dependencies.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Can't Gather Resources."));
	}
}


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
