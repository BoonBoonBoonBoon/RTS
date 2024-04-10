// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkerAttributesComponent.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "WorkerDrone.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AWorkerDrone : public AGenericBaseAI
{
	GENERATED_BODY()

public:

	AWorkerDrone();

	virtual void BeginPlay() override;
	
	UWorkerAttributesComponent* WorkerAttributesComponent;

	//UActorAttributesComponent* ActorAttributesComponent;
	
};
