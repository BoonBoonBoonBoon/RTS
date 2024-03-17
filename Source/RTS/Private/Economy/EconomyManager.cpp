// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/EconomyManager.h"


UEconomyManager::UEconomyManager()
{
}

void UEconomyManager::GlobalEconomy()
{
}

void UEconomyManager::IncomingResource(int32 IncomingResourceAmount, EResourceType IncomingResourceType)
{
	if(IncomingResourceAmount > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Transaction Process Completed, Arrived at HUB"));
		
		if(ResourceType == EResourceType::Wood)
		{
			RWoodAmount += IncomingResourceAmount;
			UE_LOG(LogTemp, Warning, TEXT("Wood Amount in Storage : %d"), RWoodAmount);
		}
		else if(ResourceType == EResourceType::Stone)
		{
			RStoneAmount += IncomingResourceAmount;
			UE_LOG(LogTemp, Warning, TEXT("Stone Amount : %d"), RStoneAmount);
		}
	}
}

void UEconomyManager::OutgoingResource(int32 ResourceAmount)
{
}


