// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "BasicSiegeAttributesComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UBasicSiegeAttributesComponent : public UActorAttributesComponent
{
	GENERATED_BODY()

protected:
	bool bCanAttack;
	bool bCanGuard;

public:
	virtual void SetCanAttack(bool bNewCanAttack) override;
	virtual void SetCanGuard(bool bNewCanGuard) override;

	virtual bool CanAttack() const override;
	virtual bool CanGuard() const override;
};
