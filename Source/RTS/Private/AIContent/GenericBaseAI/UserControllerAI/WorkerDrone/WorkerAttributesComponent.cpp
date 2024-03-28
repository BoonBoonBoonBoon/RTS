// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/WorkerDrone/WorkerAttributesComponent.h"

UWorkerAttributesComponent::UWorkerAttributesComponent()
{

}

void UWorkerAttributesComponent::SetCanGather(bool bNewCanGather)
{
	bCanGather = bNewCanGather;
}

bool UWorkerAttributesComponent::CanGather() const
{
	return bCanGather;
}
