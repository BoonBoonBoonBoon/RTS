// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSGameModeBase.h"

#include "EngineUtils.h"
#include "UserController.h"
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
	
	/*PlayerWidget->Initialize();
	
	PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), UPlayerWidget::StaticClass());
	if(PlayerWidget)
	{
		
		PlayerWidget->AddToViewport();

		UEconomyManager::GetInstance()->OnWoodChanged.AddDynamic(PlayerWidget, &UPlayerWidget::UpdateWoodAmount);
		UEconomyManager::GetInstance()->OnStoneChanged.AddDynamic(PlayerWidget, &UPlayerWidget::UpdateStoneAmount);
		UEconomyManager::GetInstance()->OnFoodChanged.AddDynamic(PlayerWidget, &UPlayerWidget::UpdateFoodAmount);
		UEconomyManager::GetInstance()->OnGoldChanged.AddDynamic(PlayerWidget, &UPlayerWidget::UpdateGoldAmount);

		UE_LOG(LogTemp, Warning, TEXT("Widget added to viewport."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create widget."));
	}*/
}

void ARTSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Resets the Economy for every playable session.
	UEconomyManager::GetInstance()->ResetEconomy();

	UpdateEWidget();

	//	UEconomyManager::EconomyWidgetRef = Cast<UPlayerWidget>(CreateWidget(GetWorld(), UPlayerWidget::StaticClass()));
}

UPlayerWidget* ARTSGameModeBase::Getter()
{
	return PlayerWidget;
}