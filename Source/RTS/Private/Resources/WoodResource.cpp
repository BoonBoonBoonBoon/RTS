// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/WoodResource.h"

AWoodResource::AWoodResource()
{
	MaxResourceAmount = 10;
	CurrentResourceAmount = MaxResourceAmount;
}

void AWoodResource::BeginPlay()
{
	Super::BeginPlay();
}

EResourceType AWoodResource::GetResourceType() const
{
	return EResourceType::Wood;
}

int32 AWoodResource::GetAmount()
{
	return CurrentResourceAmount;
}

void AWoodResource::TakeResources(int32 amount)
{
	// Later on we can check if certain upgrades have been set, For now we only take a single element at once.
	if(CurrentResourceAmount > 0)
	{
		CurrentResourceAmount -= amount; // Depletes The Resource.

		UE_LOG(LogTemp, Warning, TEXT("Wood Left In Node : %d"), CurrentResourceAmount);
	} else if (CurrentResourceAmount <= 0)
	{
		Destroy(); // Destroys The Node.
		UE_LOG(LogTemp, Warning, TEXT("No Wood Left In Node"));
	}	
}
