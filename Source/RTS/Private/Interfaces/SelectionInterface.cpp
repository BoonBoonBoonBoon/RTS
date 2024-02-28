// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SelectionInterface.h"

#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Components/DecalComponent.h"

// Add default functionality here for any ISelectionInterface functions that are not pure virtual.
void ISelectionInterface::Tick(float DeltaTime)
{
	                
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
		// No units selected, add actor.
		Selected.AddUnique(HitActor);
		for (AActor* Src : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
			{
				BaseAI->SelectedDecalComp->SetVisibility(true);
				UE_LOG(LogTemp, Warning, TEXT("Unit Selection: %d"), Selected.Num());
			}
		}
	}
	// Units already selected, clear previous selection and add the new HitActor
	else
	{
		for (AActor* Pawns : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Pawns))
			{
				BaseAI->SelectedDecalComp->SetVisibility(false);
			}
		}
		// then empties array
		Selected.Empty();
		UE_LOG(LogTemp, Warning, TEXT("Unit Selection (Select.Empty): %d"), Selected.Num());
		// adds the new incoming element
		Selected.AddUnique(HitActor);

		for (AActor* NewPawn : Selected)
		{
			if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(NewPawn))
			{
				UE_LOG(LogTemp, Warning, TEXT("Unit Selection (ForLoopAtEnd?): %d"), Selected.Num());
				// sets the new elements vis 
				BaseAI->SelectedDecalComp->SetVisibility(true);
			}
		}
	}
}
/*if (Selected.Num() == 0)
{
	//UE_LOG(LogTemp, Warning, TEXT("empty"));

	Selected.AddUnique(HitActor);
	for (AActor* Src : Selected)
	{
		if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
		{
			BaseAI->SelectedDecalComp->SetVisibility(true);
			UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), Selected.Num());
		}
	}
}
else
{
	UE_LOG(LogTemp, Warning, TEXT("empty"));

	// Loops through all the elements and turns vis off
	for (AActor* HitActor : Selected)
	{
		if (AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(HitActor))
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
}*/

void ISelectionInterface::MultiUnitSelection(TArray<AActor*> Selected, AActor* HitActor)
{
	// Loops through all possible actors 
	Selected.AddUnique(HitActor);
	for (AActor* Src : Selected)
	{
		if (const AGenericBaseAI* BaseAI = Cast<AGenericBaseAI>(Src))
		{
			BaseAI->SelectedDecalComp->SetVisibility(true);
			UE_LOG(LogTemp, Warning, TEXT("Selected Units: %d"), Selected.Num());
		}
	}
}

