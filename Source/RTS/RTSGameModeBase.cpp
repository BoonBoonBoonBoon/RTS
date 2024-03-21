// Copyright Epic Games, Inc. All Rights Reserved.


#include "RTSGameModeBase.h"
#include "UserController.h"
#include "Economy/EconomyManager.h"



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

void ARTSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Resets the Economy for every playable session.
	UEconomyManager::GetInstance()->ResetEconomy();

	
	/*
	UPlayerWidget* PlayerWidgetInstance = CreateWidget<UPlayerWidget>(this, UPlayerWidget::StaticClass());
	if (PlayerWidgetInstance != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget added to viewport."));
		PlayerWidgetInstance->AddToViewport();
	}
	*/
	
	/*// Create and display the Player Widget.
	if (UPlayerWidget* PlayerHUD = CreateWidget<UPlayerWidget>(GetWorld(), UPlayerWidget::StaticClass()))
	{
		//CreateWidget(PlayerHUD->GetClass());
		PlayerHUD->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Widget added to viewport."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create widget."));
	
	}*/
	
	
	
//	UEconomyManager::EconomyWidgetRef = Cast<UPlayerWidget>(CreateWidget(GetWorld(), UPlayerWidget::StaticClass()));
}
