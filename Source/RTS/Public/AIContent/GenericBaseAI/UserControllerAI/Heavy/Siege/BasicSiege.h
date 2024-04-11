// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseAI/UserControllerAI/Light/Scout/BasicScoutAttributesComponent.h"
#include "BasicSiege.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ABasicSiege : public AGenericBaseAI
{
	GENERATED_BODY()
public:

	ABasicSiege();

	virtual void BeginPlay() override;
	
	UBasicScoutAttributesComponent* BasicScoutAttributesComponent;
};
