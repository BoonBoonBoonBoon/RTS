// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/ResourceTransaction.h"
#include "Economy/EconomyManager.h"
#include "Resources/FoodResource.h"
#include "Resources/GoldResource.h"
#include "Resources/StoneResource.h"
#include "Resources/WoodResource.h"


// Check ENUM DataBase to use here for specific checks and what not
// Could use specifically for units and probably for buildings as well.

void UResourceTransaction::TransactionProcess(AResourceMain* ResourceRef)
{
	// Identify the Resource Type and then Process the Transaction.
	UE_LOG(LogTemp, Warning, TEXT("Transaction Process called."));
	
	if (AWoodResource* WoodResource = Cast<AWoodResource>(ResourceRef))
	{
		const int32 TakenWoodAmount = WoodResource->TakeResources(ValueForTransaction);

		UE_LOG(LogTemp, Warning, TEXT("Wood Transaction Processing."));
		
		// Push the Resource to the EM, Value amount & Resource Type.
		ProcessingTransaction(TakenWoodAmount, EResourceType::Wood);
	}
	else if (AStoneResource* StoneResource = Cast<AStoneResource>(ResourceRef))
	{
		const int32 TakenStoneAmount = StoneResource->TakeResources(ValueForTransaction);

		UE_LOG(LogTemp, Warning, TEXT("Stone Transaction Processing."));
		
		// Push the Resource to the EM, Value amount & Resource Type.
		ProcessingTransaction(TakenStoneAmount, EResourceType::Stone);
	}
	else if (AFoodResource* FoodResource = Cast<AFoodResource>(ResourceRef))
	{
		const int32 TakenFoodAmount = FoodResource->TakeResources(ValueForTransaction);

		UE_LOG(LogTemp, Warning, TEXT("Food Transaction Processing."));
		
		// Push the Resource to the EM, Value amount & Resource Type.
		ProcessingTransaction(TakenFoodAmount, EResourceType::Food);
	}
	else if (AGoldResource* GoldResource = Cast<AGoldResource>(ResourceRef))
	{
		const int32 TakenGoldAmount = GoldResource->TakeResources(ValueForTransaction);

		UE_LOG(LogTemp, Warning, TEXT("Gold Transaction Processing."));
		
		// Push the Resource to the EM, Value amount & Resource Type.
		ProcessingTransaction(TakenGoldAmount, EResourceType::Gold);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Transaction Process Failed."));
	}
}

void UResourceTransaction::ProcessingTransaction(int32 ResourceAmount, EResourceType ResourceType)
{
	// Get the Economy Manager Instance.
	UEconomyManager* EconomyManager = UEconomyManager::GetInstance();
	
	UE_LOG(LogTemp, Warning, TEXT("ProcessingTransaction :: ResourceAmount: %d"), ResourceAmount);
	
	// Process The Last of the Dispatched Resources.
	EconomyManager->IncomingResource(ResourceAmount, ResourceType);
}
	


