// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ResourceInterface.h"
#include "Resources/WoodResource.h"


// Add default functionality here for any IResourceInterface functions that are not pure virtual.

void IResourceInterface::ResourceAmount(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hi)
{
	// Cast to All Possible Variants
	EResourceType ResourceType1 = (SelfActor && SelfActor->IsA<AResourceMain>()) ? Cast<AResourceMain>(SelfActor)->GetResourceType() : EResourceType::Invalid;
	EResourceType ResourceType2 = (SelfActor && SelfActor->IsA<AWoodResource>()) ? Cast<AWoodResource>(SelfActor)->GetResourceType() : EResourceType::Invalid;
	if(ResourceType1 == EResourceType::Invalid)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid"));
	}
	else if(ResourceType2 == EResourceType::Wood)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wood"));
		
	}
}


int32 IResourceInterface::GetAmount(int Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Amount: %d"), Amount);
	return {};
}

void IResourceInterface::TakeResources(int32 Amount)
{
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
