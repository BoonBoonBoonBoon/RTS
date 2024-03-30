// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIContent/GenericBaseAI/ActorAttributesComponent.h"
#include "HarraserAttributesComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UHarraserAttributesComponent : public UActorAttributesComponent
{
	GENERATED_BODY()

public:

	virtual void SetCanAttack(bool bNewCanAttack) override;
	virtual bool CanAttack() const override;
	
	virtual void SetCanSearch(bool bNewCanSearch) override;
	virtual bool CanSearch() const override;

	
};
