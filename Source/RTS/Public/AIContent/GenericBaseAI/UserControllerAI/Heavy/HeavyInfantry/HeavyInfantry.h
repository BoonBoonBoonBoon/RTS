// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeavyInfantryAttributesComponent.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "HeavyInfantry.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AHeavyInfantry : public AGenericBaseAI
{
	GENERATED_BODY()

	UHeavyInfantryAttributesComponent* HeavyInfantryAttributesComponent;

	AHeavyInfantry();
	
	virtual void BeginPlay() override;

	
	
};
