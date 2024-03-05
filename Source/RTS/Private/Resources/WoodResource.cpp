// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/WoodResource.h"

AWoodResource::AWoodResource()
{
}

void AWoodResource::BeginPlay()
{
	Super::BeginPlay();
}

EResourceType AWoodResource::GetResourceType() const
{
	return EResourceType::Wood;
}
