// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "GameFramework/GameModeBase.h"
#include "Widets/PlayerWidget.h"
#include "RTSGameModeBase.generated.h"


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

	ARTSGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void UpdateEWidget();
	
	
	void BeginPlay() override;

	UPlayerWidget* Getter();
	
};
