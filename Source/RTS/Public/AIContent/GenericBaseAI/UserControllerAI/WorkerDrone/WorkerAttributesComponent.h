// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "WorkerAttributesComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UWorkerAttributesComponent : public UActorAttributesComponent
{
	GENERATED_BODY()

public:

	UWorkerAttributesComponent();
	
	bool bCanGather = false;
	bool bCanRepair = false;
	
	virtual void SetCanGather(bool bNewCanGather) override;
	virtual bool CanGather() const override;

	virtual void SetCanRepair(bool bNewCanRepair) override;
	virtual bool CanRepair() const override;
	
};
