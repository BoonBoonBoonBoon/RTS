// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "GameFramework/GameModeBase.h"
#include "Widets/PlayerWidget.h"
#include "RTSGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenFinishedWidget);

/**
 * 
 */
UCLASS()
class RTS_API ARTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	TArray<AGenericBaseAI*> GetAllFriendlyAI(UWorld* World);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<UPlayerWidget> PlayerWidget;

	UPROPERTY(BlueprintAssignable)
	FOpenFinishedWidget OpenFinishedWidget;

	ARTSGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void UpdateEWidget();

	// This function will be called when all enemy AI are destroyed
	void OnAllEnemiesDestroyed();

	// This function checks if there are any enemy AI left in the world
	void CheckEnemies();
	
	void BeginPlay() override;

	UPlayerWidget* Getter();
	
};
