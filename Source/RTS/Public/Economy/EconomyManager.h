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
	void ResetEconomy();

	EResourceType ResourceType;
	FResourceStats ResourceStats;

	int RWoodAmount = 0;
	int RStoneAmount = 0;
	
	// Main Function for the Economy.
	void GlobalEconomy();
	
	// Handles Incoming Resources to Deposit.
	void IncomingResource(int32 IncomingResourceAmount, EResourceType IncomingResourceType);

	void OutgoingResource(int32 ResourceAmount);	// Handles Outgoing Resources to Withdraw.
	
	// Singleton Instance.
	static UEconomyManager* GetInstance();

	void UpdateEconomyWidget();
	
	//static UPlayerWidget* EconomyWidgetRef; // The Economy Widget.

	//UPROPERTY()
	//UPlayerWidget* EconomyWidget;
	
private :
	// Singleton Instance.
	static UEconomyManager* Instance;

};
