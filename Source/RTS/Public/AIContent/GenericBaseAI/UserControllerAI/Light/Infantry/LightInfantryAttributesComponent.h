// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "LightInfantryAttributesComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ULightInfantryAttributesComponent : public UActorAttributesComponent
{
	GENERATED_BODY()

public:

	ULightInfantryAttributesComponent();
	
	bool bCanAttack;
	bool bCanGuard;
	bool bCanPatrol;
	
	virtual void SetCanAttack(bool bNewCanAttack) override;
	virtual void SetCanGuard(bool bNewCanGuard) override;
	virtual void SetCanPatrol(bool bNewCanPatrol) override;

	virtual bool CanAttack() const override;
	virtual bool CanGuard() const override;
	virtual bool CanPatrol() const override;

	// Extra

	bool bCanGather = false;
	
	virtual void SetCanGather(bool bNewCanGather) override;
	virtual bool CanGather() const override;
};
