// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Light/Infantry/LightInfantryAttributesComponent.h"

ULightInfantryAttributesComponent::ULightInfantryAttributesComponent()
{
}

void ULightInfantryAttributesComponent::SetCanGather(bool bNewCanGather)
{
	bCanGather = bNewCanGather;
}

bool ULightInfantryAttributesComponent::CanGather() const
{
	return bCanGather;
}
