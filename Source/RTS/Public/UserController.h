// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UserCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "UserCharacter.h"
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

	UPROPERTY()
	AUserController* MyController = this;
	
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

	// Changes the length of the CameraBoom
	void ZoomIn(float Value);
	void ZoomOut(float Value);

	// Rotates the camera 
	void Left_Camera_Rotation();
	void Right_Camera_Rotation();
	
protected:
	

	
	//FORCEINLINE class AUserCharacter* GetUserCharacter() const { return UserCharacter; }
	//int32 ArmLength = GetUserCharacter()->GetCameraBoom()->TargetArmLength;
	
	// The Cursors Location
	FVector2D MousePosition;
	
	FVector2D InitialMousePosition;
	// Updated Cursor location
	FVector2d CurrentMousePosition;
	
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

	// Susceptible to Change
	int32 MaxZoom = 4000;
	int32 MinZoom = 1000;

	float ZoomRate = 30;
	float MouseDownTime;
	float Dist;

	UDecalComponent* CursorToWorld;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class AUserCharacter* UserCharacter;
	
	void StartBoxSelection();
	void EndBoxSelection();
	
	// Checks if the cursor has moved from it original location 
	bool HasCursorMoved();
	// Hits the units that are selected
	void UnitSelection();
	// What happens when pawn selected
	void HandlePawnSelection(APawn* HitPawn);
	// Updates the Marquee edges 
	void Update();
	// Draws The Marquee Tool 
	void Draw2DSSquare(const FVector Edge1, FVector2D& Edge2); // Direction?
	
	FHitResult bHit; 
	
};
