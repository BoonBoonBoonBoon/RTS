// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/FoodResource.h"

AFoodResource::AFoodResource()
{
	MaxResourceAmount = 10;
	CurrentFoodAmount = MaxResourceAmount;

	Tags.Add("Resource");
}

EResourceType AFoodResource::GetResourceType() const
{
	return EResourceType::Food;
}

int32 AFoodResource::GetAmount()
{
	return CurrentFoodAmount;
}

int32 AFoodResource::TakeResources(int32 amount)
{
	// Later on we can check if certain upgrades have been set, For now we only take a single element at once.
	if(CurrentFoodAmount > 0)
	{
		const int32 TakenAmount = FMath::Min(amount, CurrentFoodAmount); // Takes the Smallest Value between the two.
		CurrentFoodAmount -= TakenAmount; // Depletes The Resource.
		UE_LOG(LogTemp, Warning, TEXT("Food Left In Node : %d"), CurrentFoodAmount);
		return TakenAmount;
	}
	else
	{
		Destroy(); // Destroys The Node.
		UE_LOG(LogTemp, Warning, TEXT("No Food Left In Node"));
		return 0;
	}
}