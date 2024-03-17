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

int32 AWoodResource::TakeResources(int32 amount)
{
	// Later on we can check if certain upgrades have been set, For now we only take a single element at once.
	if(CurrentResourceAmount > 0)
	{
		const int32 TakenAmount = FMath::Min(amount, CurrentResourceAmount); // Takes the Smallest Value between the two.
		CurrentResourceAmount -= TakenAmount; // Depletes The Resource.
		UE_LOG(LogTemp, Warning, TEXT("Wood Left In Node : %d"), CurrentResourceAmount);
		return TakenAmount;
	}
	else
	{
		Destroy(); // Destroys The Node.
		UE_LOG(LogTemp, Warning, TEXT("No Wood Left In Node"));
		return 0;
	}
}
