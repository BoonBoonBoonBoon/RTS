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

void AWoodResource::TakeResources(int32 amount)
{
	Super::TakeResources(amount);
}
