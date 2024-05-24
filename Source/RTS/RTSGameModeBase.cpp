// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSGameModeBase.h"

#include "EngineUtils.h"
#include "UserController.h"
#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"
#include "Blueprint/UserWidget.h"
#include "Economy/EconomyManager.h"

TArray<AGenericBaseAI*> ARTSGameModeBase::GetAllFriendlyAI(UWorld* World)
{
	TArray<AGenericBaseAI*> GenericBaseAIUnits;

	for (TActorIterator<AGenericBaseAI> It(World); It; ++It)
	{
		GenericBaseAIUnits.Add(*It);
	}

	return GenericBaseAIUnits;
}

ARTSGameModeBase::ARTSGameModeBase()
{
	// use the custom Controller class
	PlayerControllerClass = AUserController::StaticClass();

	// Set default pawn class to our bp character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("UserContent/UserControl/BP_UserCharacter.uasset"));
	if(PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ARTSGameModeBase::UpdateEWidget()
{
	
}

void ARTSGameModeBase::OnAllEnemiesDestroyed()
{
	OpenFinishedWidget.Broadcast();
}

void ARTSGameModeBase::CheckEnemies()
{
	for (TActorIterator<AGenericBaseEnemyAI> It(GetWorld()); It; ++It)
	{
		// If an enemy AI is found, return
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("All Enemies Destroyed"));
	
	// If no enemy AI are found, call OnAllEnemiesDestroyed
	OnAllEnemiesDestroyed();
}

void ARTSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Resets the Economy for every playable session.
	UEconomyManager::GetInstance()->ResetEconomy();

	UpdateEWidget();
	
}

UPlayerWidget* ARTSGameModeBase::Getter()
{
	return PlayerWidget;
}