// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API ISelectionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Tick(float DeltaTime);
	
	UFUNCTION()
	virtual void StartBoxSelection();

	UFUNCTION()
	virtual void EndBoxSelection();

	// Checks if the cursor has moved from it original location 
	bool HasCursorMoved();

	// Hits the units that are selected
	UFUNCTION()
	virtual void UnitSelection();

	// What happens when pawn selected
	void UnitSelection(TArray<AActor*> Selected, AActor* HitActor);

	void MultiUnitSelection(TArray<AActor*> Selected, AActor* HitActor);

};
