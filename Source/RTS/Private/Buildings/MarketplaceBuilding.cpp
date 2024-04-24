// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/MarketplaceBuilding.h"

#include "Interfaces/SelectionInterface.h"

AMarketplaceBuilding::AMarketplaceBuilding()
{
	
}

EBuildingTypes AMarketplaceBuilding::GetBuildingType(EBuildingTypes BuildingType)
{
	return BuildingType = EBuildingTypes::Trader;
}

void AMarketplaceBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	SelectionInterface->AssignBuildingType(this);
}

/*
void AMarketplaceBuilding::GetBuildingType(EBuildingTypes BuildingType)
{
}
*/
