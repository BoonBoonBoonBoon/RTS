// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/WoodResource.h"

AWoodResource::AWoodResource()
{
	MaxResourceAmount = 10;
	CurrentWoodAmount = MaxResourceAmount;
	Tags.Add("Resource");
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
	return CurrentWoodAmount;
}

int32 AWoodResource::TakeResources(int32 amount)
{
	// Later on we can check if certain upgrades have been set, For now we only take a single element at once.
	if(CurrentWoodAmount > 0)
	{
		const int32 TakenAmount = FMath::Min(amount, CurrentWoodAmount); // Takes the Smallest Value between the two.
		CurrentWoodAmount -= TakenAmount; // Depletes The Resource.
		UE_LOG(LogTemp, Warning, TEXT("Wood Left In Node : %d"), CurrentWoodAmount);
		return TakenAmount;
	}
	else
	{
		Destroy(); // Destroys The Node.
		UE_LOG(LogTemp, Warning, TEXT("No Wood Left In Node"));
		return 0;
	}
}
