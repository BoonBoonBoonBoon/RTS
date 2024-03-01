// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/MarketplaceBuilding.h"

#include "Interfaces/SelectionInterface.h"

AMarketplaceBuilding::AMarketplaceBuilding()
{
	//BuildingType = EBuildingTypes::Trader;
}

EBuildingTypes AMarketplaceBuilding::GetBuildingType(EBuildingTypes BuildingType)
{
	return BuildingType = EBuildingTypes::Trader;
}

/*
void AMarketplaceBuilding::GetBuildingType(EBuildingTypes BuildingType)
{
}
*/
