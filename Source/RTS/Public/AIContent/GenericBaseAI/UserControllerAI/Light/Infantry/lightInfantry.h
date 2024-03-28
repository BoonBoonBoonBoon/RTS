// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "lightInfantry.generated.h"



/**
 * 
 */
UCLASS()
class RTS_API AlightInfantry : public AGenericBaseAI
{
	GENERATED_BODY()

public:
	UActorAttributesComponent* ActorAttributesComponent;
	
	AlightInfantry();
	
};
