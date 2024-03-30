// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Heavy/Siege/BasicSiegeAttributesComponent.h"

void UBasicSiegeAttributesComponent::SetCanAttack(bool bNewCanAttack)
{
	bCanAttack = bNewCanAttack;
}

void UBasicSiegeAttributesComponent::SetCanGuard(bool bNewCanGuard)
{
	bCanGuard = bNewCanGuard;
}

bool UBasicSiegeAttributesComponent::CanAttack() const
{
	return bCanAttack;
}

bool UBasicSiegeAttributesComponent::CanGuard() const
{
	return bCanGuard;
}
