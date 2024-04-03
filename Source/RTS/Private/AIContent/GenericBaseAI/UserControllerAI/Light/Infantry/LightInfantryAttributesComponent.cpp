// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/LightInfantryAttributesComponent.h"

ULightInfantryAttributesComponent::ULightInfantryAttributesComponent()
{
}

void ULightInfantryAttributesComponent::SetCanAttack(bool bNewCanAttack)
{
	bCanAttack = bNewCanAttack;
}

void ULightInfantryAttributesComponent::SetCanGuard(bool bNewCanGuard)
{
	bCanGuard = bNewCanGuard;
}

void ULightInfantryAttributesComponent::SetCanPatrol(bool bNewCanPatrol)
{
	bCanPatrol = bNewCanPatrol;
}

bool ULightInfantryAttributesComponent::CanAttack() const
{
	return bCanAttack;
}

bool ULightInfantryAttributesComponent::CanGuard() const
{
	return bCanGuard;
}

bool ULightInfantryAttributesComponent::CanPatrol() const
{
	return bCanPatrol;
}

// Extra

void ULightInfantryAttributesComponent::SetCanGather(bool bNewCanGather)
{
	bCanGather = false;
}

bool ULightInfantryAttributesComponent::CanGather() const
{
	return bCanGather;
}

