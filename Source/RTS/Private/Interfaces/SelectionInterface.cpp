// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SelectionInterface.h"

// Add default functionality here for any ISelectionInterface functions that are not pure virtual.
void ISelectionInterface::Tick(float DeltaTime)
{
	Update();
}

void ISelectionInterface::StartBoxSelection()
{


}

void ISelectionInterface::EndBoxSelection()
{
}

bool ISelectionInterface::HasCursorMoved()
{
	return true;
}

void ISelectionInterface::UnitSelection()
{
}

void ISelectionInterface::HandlePawnSelection(APawn* HitPawn)
{
}

void ISelectionInterface::Update()
{
}
