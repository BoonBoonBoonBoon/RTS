// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ResourceInterface.h"
#include "EconomyManager.generated.h"
/**
 * 
 */


UCLASS()
class RTS_API UEconomyManager : public UObject
{
	GENERATED_BODY()
	
public:
	UEconomyManager();
	
	EResourceType ResourceType;
	FResourceStats ResourceStats;

	int RWoodAmount;
	int RStoneAmount;
	
	
	// Main Function for the Economy.
	void GlobalEconomy();
	
	// Handles Incoming Resources to Deposit.
	void IncomingResource(int32 IncomingResourceAmount, EResourceType IncomingResourceType);

	void OutgoingResource(int32 ResourceAmount);	// Handles Outgoing Resources to Withdraw.
	
};
