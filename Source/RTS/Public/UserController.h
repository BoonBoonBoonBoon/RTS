// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UserController.generated.h"


class UDecalComponent;
class UBoxComponent;
class AUserCharacter;


/**
 * 
 */
UCLASS()
class RTS_API AUserController : public APlayerController
{
	GENERATED_BODY()

public:
	
	AUserController();
	virtual void OnPossess(APawn* InPawn) override;

	// Checks if the cursor is near the edges of the screen and moves it accordingly 
	void EdgeScrolling();

	// Moves the camera in the direction of the cursor direction
	void MoveCamera(const FVector& Direction);

protected:

	// The Cursors Location
	FVector2D MousePosition;
	// Returns the viewport Size
	FVector2D ViewportSize;

	bool bCheckCursor;
	
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
