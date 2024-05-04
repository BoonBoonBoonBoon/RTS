// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/GoldResource.h"

AGoldResource::AGoldResource()
{
	MaxResourceAmount = 10;
	CurrentGoldAmount = MaxResourceAmount;
	Tags.Add("Resource");
}

EResourceType AGoldResource::GetResourceType() const
{
	return EResourceType::Gold;
}

int32 AGoldResource::GetAmount()
{
	return CurrentGoldAmount;
}

int32 AGoldResource::TakeResources(int32 amount)
{
	// Later on we can check if certain upgrades have been set, For now we only take a single element at once.
	if(CurrentGoldAmount > 0)
	{
		const int32 TakenAmount = FMath::Min(amount, CurrentGoldAmount); // Takes the Smallest Value between the two.
		CurrentGoldAmount -= TakenAmount; // Depletes The Resource.
		UE_LOG(LogTemp, Warning, TEXT("Gold Left In Node : %d"), CurrentGoldAmount);
		return TakenAmount;
	}
	else
	{
		Destroy(); // Destroys The Node.
		UE_LOG(LogTemp, Warning, TEXT("No Gold Left In Node"));
		return 0;
	}
}