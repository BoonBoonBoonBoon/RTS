// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Light/Ranged/RangedAttributesComponent.h"

void URangedAttributesComponent::SetCanAttack(bool bNewCanAttack)
{
	bCanAttack = bNewCanAttack;
}

void URangedAttributesComponent::SetCanGuard(bool bNewCanGuard)
{
	bCanGuard = bNewCanGuard;
}

bool URangedAttributesComponent::CanAttack() const
{
	return bCanAttack;
}

bool URangedAttributesComponent::CanGuard() const
{
	return bCanGuard;
}