// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UserCharacter.h"
#include "GameFramework/PlayerController.h"
#include "RTS/Public/Interfaces/SelectionInterface.h"
#include "GameFramework/SpringArmComponent.h"
#include "UserCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UserController.generated.h"


class UDecalComponent;
class UBoxComponent;


/**
 * 
 */
UCLASS()
class RTS_API AUserController : public APlayerController
{
	GENERATED_BODY()

	AUserCharacter* UserCharacter;
	
	UPROPERTY()
	AUserController* MyController = this;
	
	USelectionInterface* SelectionInterface;
public:
	
	AUserController();
	virtual void OnPossess(APawn* InPawn) override;
	
	// Checks if the cursor is near the edges of the screen and moves it accordingly 
	void EdgeScrolling();
	void EdgeScrolling_WASD_Up(float Value);
	void EdgeScrolling_WASD_Down(float Value); 
	void EdgeScrolling_WASD_Right(float Value); 
	void EdgeScrolling_WASD_Left(float Value); 

	// Moves the camera in the direction of the cursor direction
	void MoveCamera(const FVector& Direction);


protected:
	
	//FORCEINLINE class AUserCharacter* GetUserCharacter() const { return UserCharacter; }
	//int32 ArmLength = GetUserCharacter()->GetCameraBoom()->TargetArmLength;
	
	// The Cursors Location
	FVector2D MousePosition;

public:
	UPROPERTY(BlueprintReadWrite)
	FVector2D InitialMousePosition;
	
	//NewMousePos
	UPROPERTY(BlueprintReadWrite)
	FVector2D NewMousePosition;

	FVector2D STEdge1;
	FVector2D STEdge2;

	UPROPERTY(BlueprintReadWrite)
	bool CursorMoved = false;

	TArray<AActor*> ActorsInSelection;
	
protected:

	UBoxComponent* SelectionArea;
	
	// Returns the viewport Size
	FVector2D ViewportSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Selection")
	bool bIsSelecting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Selection")
	bool bIsMultiSelecting;
	
	bool bCheckCursor;
	bool bCursorMove;
	
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	/*
	FVector TargetLocation; 
	FRotator TargetRotation;

	bool CanRotate;
	
	float RotateSpeed = 2.f;
	float RotatePitchMin = 10.f;
	float RotatePitchMax = 80.f;
	*/
	
	float TargetZoom = 3000.f;
	float ZoomSpeed = 2.f;
	
	// Susceptible to Change
	int32 MaxZoom = 4000.f;
	int32 MinZoom = 500.f;

	float ZoomRate = 30;
	float MouseDownTime;
	float Dist;

	UDecalComponent* CursorToWorld;
	
public:

	UFUNCTION(BlueprintCallable)
	void StartBoxSelection();
	UFUNCTION(BlueprintCallable)
	void EndBoxSelection();


	TArray<AActor*> SelectedUnits;

	// Shift + LMS for multi-selection of individual units 
	UFUNCTION()
	void MultiSelect();

	// Checks if we are selecting multiple ai
	bool MultiselectCond;
	
	// Checks if the cursor has moved from it original location
	UFUNCTION(BlueprintCallable)
	bool HasCursorMoved();
	
	// Hits the units that are selected
	UFUNCTION(BlueprintCallable)
	void UnitSelection();

	bool bNotHit;
	
	// What happens when pawn selected
	UFUNCTION(BlueprintCallable)
	void HandlePawnSelection(APawn* HitPawn);
	
	// Updates the Marquee edges
	UFUNCTION(BlueprintCallable)
	void UpdateFlow();
	
	// Draws The Marquee Tool 
	void Draw2DSSquare(const FVector Edge1, FVector2D& Edge2); // Direction?
	
	FHitResult bHit; 
	
};
