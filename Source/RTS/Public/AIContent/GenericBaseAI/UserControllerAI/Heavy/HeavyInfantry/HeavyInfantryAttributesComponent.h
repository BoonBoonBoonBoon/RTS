// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "HeavyInfantryAttributesComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UHeavyInfantryAttributesComponent : public UActorAttributesComponent
{
	GENERATED_BODY()

public:

	bool bCanAttack;
	bool bCanGuard;
	bool bcanPatrol;
	
	
protected:

	virtual void SetCanAttack(bool bNewCanAttack) override;
	virtual void SetCanGuard(bool bNewCanGuard) override;
	virtual void SetCanPatrol(bool bNewCanPatrol) override;

	virtual bool CanAttack() const override;
	virtual bool CanGuard() const override;
	virtual bool CanPatrol() const override;
	
};
