// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RangedAttributesComponent.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Ranged.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARanged : public AGenericBaseAI
{
	GENERATED_BODY()

	ARanged();

	virtual void BeginPlay() override;

	URangedAttributesComponent* RangedAttributesComponent;
};
