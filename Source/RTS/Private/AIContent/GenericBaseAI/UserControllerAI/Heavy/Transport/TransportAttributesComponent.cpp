// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Heavy/Transport/TransportAttributesComponent.h"

void UTransportAttributesComponent::SetCanTransport(bool bNewCanAttack)
{
	bCanTansport = bNewCanAttack;
}

bool UTransportAttributesComponent::CanTransport() const
{
	return bCanTansport;
}
