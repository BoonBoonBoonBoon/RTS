// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/EconomyManager.h"

#include "Kismet/GameplayStatics.h"
#include "RTS/RTSGameModeBase.h"


//UPlayerWidget* UEconomyManager::EconomyWidgetRef = nullptr;

//: ResourceType(), ResourceStats(), EconomyWidget(nullptr)
UEconomyManager::UEconomyManager()
{
	//WoodAmountChanged.AddDynamic(EconomyWidget, &UPlayerWidget::SetDisplayWoodAmount);
}

void UEconomyManager::ResetEconomy()
{
	RWoodAmount = 0;
	RStoneAmount = 0;
	RFoodAmount = 0;
	RGoldAmount = 0;
	//UE_LOG(LogTemp, Warning, TEXT("EconomyManager GameMode Reset : %d"), RWoodAmount);
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
			UpdateEconomyWidget();
		}
		else if(IncomingResourceType == EResourceType::Stone)
		{
			RStoneAmount += IncomingResourceAmount;
			UE_LOG(LogTemp, Warning, TEXT("Stone Amount : %d"), RStoneAmount);
		}
		else if(IncomingResourceType == EResourceType::Food)
		{
			RFoodAmount += IncomingResourceAmount;
			UE_LOG(LogTemp, Warning, TEXT("Food Amount : %d"), RFoodAmount);
		}
			else if(IncomingResourceType == EResourceType::Stone)
		{
			RGoldAmount += IncomingResourceAmount;
			UE_LOG(LogTemp, Warning, TEXT("Gold Amount : %d"), RGoldAmount);
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
	
	 //GameModeRef = (ARTSGameModeBase*)GetWorld()->GetAuthGameMode();

	/*
	GameModeRef = Cast<ARTSGameModeBase>(UGameplayStatics::GetGameMode(GetOuter()->GetWorld()));
	
	if(GameModeRef != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode IS VALID!!."));
		EconomyWidget = GameModeRef->Getter();
		
		if(EconomyWidget)
		{
			EconomyWidget->SetDisplayWoodAmount(RWoodAmount);
			UE_LOG(LogTemp, Warning, TEXT("EconomyWidget is Valid."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("EconomyWidget is Invalid."));
		}
	}
	*/

	

	/*if(EconomyWidget)
	{
		//EconomyWidget->SetDisplayWoodAmount(RWoodAmount);
	}*/
	
	/*if(EconomyWidget)
	{
		auto EcomWidgetInstance = Cast<UPlayerWidget>(EconomyWidget);
		if(EcomWidgetInstance)
		{
			EcomWidgetInstance->SetDisplayWoodAmount(RWoodAmount);
		}
	}*/

	/*ARTSGameModeBase* GameMode = Cast<ARTSGameModeBase>(GetWorld());
	if(GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode."));
	}*/
}



