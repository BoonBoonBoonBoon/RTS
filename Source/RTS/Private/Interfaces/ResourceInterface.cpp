// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ResourceInterface.h"
#include "Economy/ResourceTransaction.h"
#include "Resources/WoodResource.h"


// Add default functionality here for any IResourceInterface functions that are not pure virtual.


void IResourceInterface::TakeResourceObject(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hi)
{
	/*TArray<EUnitAttributes> ActorAttributes = OtherActor->GetAttributes();
	if(ActorAttributes.Contains(EUnitAttributes::Gather))
	{
		// We Want to do something with collection on this.
		
	}*/
	// Cast to All Possible Variants
	const EResourceType ResourceType1 = (SelfActor && SelfActor->IsA<AResourceMain>()) ? Cast<AResourceMain>(SelfActor)->GetResourceType() : EResourceType::Invalid;
	const EResourceType ResourceType2 = (SelfActor && SelfActor->IsA<AWoodResource>()) ? Cast<AWoodResource>(SelfActor)->GetResourceType() : EResourceType::Invalid;
	
	// Creates a new object of the Resource Transaction Class.
	UResourceTransaction* ResourceTransaction = NewObject<UResourceTransaction>();
	
	if(ResourceType1 == EResourceType::Invalid)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid"));
		ResourceTransaction->TransactionProcess(Cast<AResourceMain>(SelfActor));
	}
	else if(ResourceType2 == EResourceType::Wood)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wood"));
		ResourceTransaction->TransactionProcess(Cast<AWoodResource>(SelfActor));
		
		// Use transaction class. where in function we tell wood resource to reduce its int, and resource interface to increase its int.
		//Mediator Pattern: Introduce a mediator class that handles communication between classes. Instead of classes communicating directly with each other, they communicate through the mediator, which reduces direct dependencies.
		
		
		//int32 Wood = WoodResource->TakeResources(Resource); // Takes The Resource from the Node.
		//UE_LOG(LogTemp, Warning, TEXT("Wood value taking resources: %d"), Wood);
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
