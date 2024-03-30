// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Heavy/HeavyInfantry/HeavyInfantryAttributesComponent.h"



void UHeavyInfantryAttributesComponent::SetCanAttack(bool bNewCanAttack)
{
	bCanAttack = bNewCanAttack;
}

void UHeavyInfantryAttributesComponent::SetCanGuard(bool bNewCanGuard)
{
	bCanGuard = bNewCanGuard;
}

void UHeavyInfantryAttributesComponent::SetCanPatrol(bool bNewCanPatrol)
{
	bcanPatrol = bNewCanPatrol;
}

bool UHeavyInfantryAttributesComponent::CanAttack() const
{
	return bCanAttack;
}

bool UHeavyInfantryAttributesComponent::CanGuard() const
{
	return bCanGuard;
}

bool UHeavyInfantryAttributesComponent::CanPatrol() const
{
	return bcanPatrol;
}

