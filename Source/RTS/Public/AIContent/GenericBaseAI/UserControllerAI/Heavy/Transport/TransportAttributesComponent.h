// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "TransportAttributesComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UTransportAttributesComponent : public UActorAttributesComponent
{
	GENERATED_BODY()
	
public:
	bool bCanTansport;
	
	virtual void SetCanTransport(bool bNewCanAttack) override;

	virtual bool CanTransport() const override;
};
