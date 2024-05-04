// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/StoneResource.h"

AStoneResource::AStoneResource()
{
	MaxResourceAmount = 10;
	CurrentStoneAmount = MaxResourceAmount;
	Tags.Add("Resource");
}

EResourceType AStoneResource::GetResourceType() const
{
	return EResourceType::Stone;
}

int32 AStoneResource::GetAmount()
{
	return CurrentStoneAmount;
}

int32 AStoneResource::TakeResources(int32 amount)
{
	// Later on we can check if certain upgrades have been set, For now we only take a single element at once.
	if(CurrentStoneAmount > 0)
	{
		const int32 TakenAmount = FMath::Min(amount, CurrentStoneAmount); // Takes the Smallest Value between the two.
		CurrentStoneAmount -= TakenAmount; // Depletes The Resource.
		UE_LOG(LogTemp, Warning, TEXT("stone Left In Node : %d"), CurrentStoneAmount);
		return TakenAmount;
	}
	else
	{
		Destroy(); // Destroys The Node.
		UE_LOG(LogTemp, Warning, TEXT("No stone Left In Node"));
		return 0;
	}
}
