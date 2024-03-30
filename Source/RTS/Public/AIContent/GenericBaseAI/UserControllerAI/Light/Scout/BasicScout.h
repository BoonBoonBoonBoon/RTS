// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicScoutAttributesComponent.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "BasicScout.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ABasicScout : public AGenericBaseAI
{
	GENERATED_BODY()
public:

	UBasicScoutAttributesComponent* ScoutAttributesComponent;
	
	ABasicScout();
	
};
