// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/ResourceTransaction.h"
#include "Economy/EconomyManager.h"
#include "Resources/WoodResource.h"


// Check ENUM DataBase to use here for specific checks and what not
// Could use specifically for units and probably for buildings as well.

void UResourceTransaction::TransactionProcess(AResourceMain* ResourceRef)
{
	// Identify the Resource Type and then Process the Transaction.
	if(Cast<AWoodResource>(ResourceRef))
	{
		if(AWoodResource* WoodResource = Cast<AWoodResource>(ResourceRef))
		{
			const int32 TakenWoodAmount = WoodResource->TakeResources(ValueForTransaction);
			
			// Push the Resource to the EM, Value amount & Resource Type.
			ProcessingTransaction(TakenWoodAmount, EResourceType::Wood);
		}
	}
	else if(Cast<AResourceMain>(ResourceRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("Transaction Process Fired Up (MAIN)"));
	}
}

void UResourceTransaction::ProcessingTransaction(int32 ResourceAmount, EResourceType ResourceType)
{
	// Get the Economy Manager Instance.
	UEconomyManager* EconomyManager = UEconomyManager::GetInstance();

	// Process The Last of the Dispatched Resources.
	EconomyManager->IncomingResource(ResourceAmount, ResourceType);
}
	


