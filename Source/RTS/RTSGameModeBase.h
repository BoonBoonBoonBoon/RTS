// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UPlayerWidget* PlayerWidget;

	ARTSGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void UpdateEWidget();
	
	
	void BeginPlay() override;

	UPlayerWidget* Getter();
	
};
