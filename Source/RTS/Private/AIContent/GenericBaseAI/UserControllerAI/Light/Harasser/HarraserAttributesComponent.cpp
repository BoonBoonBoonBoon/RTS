// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/UserControllerAI/Light/Harasser/HarraserAttributesComponent.h"

void UHarraserAttributesComponent::SetCanAttack(bool bNewCanAttack)
{
	bCanAttack = bNewCanAttack;
}

bool UHarraserAttributesComponent::CanAttack() const
{
	return bCanAttack;
}

void UHarraserAttributesComponent::SetCanSearch(bool bNewCanSearch)
{
	bCanSearch = bNewCanSearch;
}

bool UHarraserAttributesComponent::CanSearch() const
{
	return bCanSearch;
}