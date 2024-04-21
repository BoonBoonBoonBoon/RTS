// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ResourceInterface.h"
#include "RTS/RTSGameModeBase.h"
#include "EconomyManager.generated.h"
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWoodChanged, int32, WoodAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoneChanged, int32, StoneAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFoodChanged, int32, FoodAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChanged, int32, GoldAmount);

class UPlayerWidget;

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
	int RFoodAmount = 0;
	int RGoldAmount = 0;
	// Main Function for the Economy.
	void GlobalEconomy();
	
	// Handles Incoming Resources to Deposit.
	void IncomingResource(int32 IncomingResourceAmount, EResourceType IncomingResourceType);

	void OutgoingResource(int32 ResourceAmount);	// Handles Outgoing Resources to Withdraw.
	
	// Singleton Instance.
	static UEconomyManager* GetInstance();

	void UpdateEconomyWidget();
	
	//UPROPERTY()
	UPlayerWidget* EconomyWidget;
	
	ARTSGameModeBase* GameModeRef;
	
	
	FOnWoodChanged OnWoodChanged;
	FOnStoneChanged OnStoneChanged;
	FOnFoodChanged OnFoodChanged;
	FOnGoldChanged OnGoldChanged;

private :
	// Singleton Instance.
	static UEconomyManager* Instance;

};
