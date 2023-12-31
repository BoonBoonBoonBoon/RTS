// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserController.h"
#include "GameFramework/HUD.h"
#include "SelectionTool.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ASelectionTool : public AHUD
{
	GENERATED_BODY()

public:
	// Draw Hud is called every frame, used for custom drawing operations.
	virtual void DrawHUD() override;


	class AUserController* Controller;
	
};
