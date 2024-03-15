// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/WoodResource.h"

AWoodResource::AWoodResource()
{
	MaxResourceAmount = 1000;
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
	
	amount = 1;
	
	CurrentResourceAmount -= amount; // Depletes The Resource.
	
	UE_LOG(LogTemp, Warning, TEXT("Wood Left In Node : %d"), CurrentResourceAmount);
	
	return amount;
	

	
}
