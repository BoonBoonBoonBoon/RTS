// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ResourceInterface.h"

/*
// Add default functionality here for any IResourceInterface functions that are not pure virtual.
FString IResourceInterface::GetEnumName()
{
	return {};
}

void IResourceInterface::TakeResources(int32 amount)
{
}
*/
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

/*
int32 IResourceInterface::GetAmount()
{
	return 0;
}
*/
void IResourceInterface::AssignResourceType(AActor* Actor)
{
	
	ActorCollect = Actor;
	UE_LOG(LogTemp, Warning, TEXT("Assign ResourceType : %s"), *ActorCollect->GetName());
}
