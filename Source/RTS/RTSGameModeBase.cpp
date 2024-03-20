// Copyright Epic Games, Inc. All Rights Reserved.


#include "RTSGameModeBase.h"
#include "UserController.h"
#include "Economy/EconomyManager.h"
#include "Widets/PlayerWidget.h"


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
	// Create and display the Player Widget.
	UPlayerWidget* PlayerHUD = CreateWidget<UPlayerWidget>(GetWorld(), UPlayerWidget::StaticClass());
	if (PlayerHUD)
	{
		//CreateWidget(PlayerHUD->GetClass());
		PlayerHUD->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Widget added to viewport."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create widget."));
	
	}
	*/
	
	
//	UEconomyManager::EconomyWidgetRef = Cast<UPlayerWidget>(CreateWidget(GetWorld(), UPlayerWidget::StaticClass()));
}
