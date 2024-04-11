// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HarraserAttributesComponent.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Harasser.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AHarasser : public AGenericBaseAI
{
	GENERATED_BODY()

	AHarasser();

	virtual void BeginPlay() override;

	UHarraserAttributesComponent* HarraserAttributesComponent;
};
