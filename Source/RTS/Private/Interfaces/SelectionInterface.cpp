// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SelectionInterface.h"

#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Components/DecalComponent.h"

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

void ISelectionInterface::UnitSelection(TArray<AActor*> Selected, AActor* HitActor)
{
	if (Selected.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("empty"));

		Selected.AddUnique(HitActor);
		for (AActor* Src : Selected)
		{
			Src->Tags.AddUnique(TEXT("SelectedPawn"));
			if (Src->Tags.Contains(TEXT("SelectedPawn")))
			{
				if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
				{
					BaseAI->SelectedDecalComp->SetVisibility(true);
					UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), Selected.Num());
				}
			}
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("empty"));

		// Loops through all the elements and turns vis off
		for (AActor* Pawns : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Pawns))
			{
				BaseAI->SelectedDecalComp->SetVisibility(false);
			}
		}
		// then empties array
		Selected.Empty();

		// adds the new incoming element
		Selected.AddUnique(HitActor);

		for (AActor* NewPawn : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(NewPawn))
			{
				// sets the new elements vis 
				BaseAI->SelectedDecalComp->SetVisibility(true);
			}
		}
	}
}

void ISelectionInterface::MultiUnitSelection(TArray<AActor*> Selected, AActor* HitActor)
{
	// Loops through all possible actors 
	Selected.AddUnique(HitActor);
	for (AActor* Src : Selected)
	{
		Src->Tags.AddUnique(TEXT("SelectedPawn"));
		if (Src->Tags.Contains(TEXT("SelectedPawn")))
		{
			if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
			{
				BaseAI->SelectedDecalComp->SetVisibility(true);
				UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), Selected.Num());
			}
		}
	}
}


void ISelectionInterface::Update()
{
}
