// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/EconomyManager.h"


UEconomyManager::UEconomyManager(): ResourceType(), ResourceStats()
{
	
}

void UEconomyManager::ResetEconomy()
{
	RWoodAmount = 0;
	UE_LOG(LogTemp, Warning, TEXT("EconomyManager GameMode Reset : %d"), RWoodAmount);
}

void UEconomyManager::GlobalEconomy()
{
}

void UEconomyManager::IncomingResource(int32 IncomingResourceAmount, EResourceType IncomingResourceType)
{
	if(IncomingResourceAmount > 0)
	{
		if(IncomingResourceType == EResourceType::Wood)
		{
			RWoodAmount += IncomingResourceAmount;
			UE_LOG(LogTemp, Warning, TEXT("Wood Amount Stored At HUB: %d"), RWoodAmount);
		}
		else if(IncomingResourceType == EResourceType::Stone)
		{
			RStoneAmount += IncomingResourceAmount;
			UE_LOG(LogTemp, Warning, TEXT("Stone Amount : %d"), RStoneAmount);
		}
	}
}

void UEconomyManager::OutgoingResource(int32 ResourceAmount)
{
}

// Singleton Instance.
UEconomyManager* UEconomyManager::Instance = nullptr;

UEconomyManager* UEconomyManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = NewObject<UEconomyManager>(); // Create a new instance of the Economy Manager.
		//Instance->AddToRoot(); // Add to Root to prevent Garbage Collection.
	}
	return Instance; // Return the Instance.
}

void UEconomyManager::UpdateEconomyWidget()
{
	if(EconomyWidget)
	{
		auto EconomyWidgetInstance = Cast<EconomyWidget>(EconomyWidget);
	}
}

