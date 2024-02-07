// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "NiagaraSystem.h"
#include "UserCharacter.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DecalActor.h"
#include "EQS/WayPointActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "RTS/Public/Interfaces/SelectionInterface.h"
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

	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	AUserCharacter* UserCharacter;

	
	AAIController* AiCon;
	
	UPROPERTY()
	AUserController* MyController = this;
	
	USelectionInterface* SelectionInterface;

	
public:

	//AGenericBaseAIController* GenAIController;

	// The Box to be drawn
	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;
	// The area the box spawns 
	FVector BoxHitLocation;

	
	
	UPROPERTY(EditAnywhere)
	AGenericBaseAI* GenericBaseAI;
	AWayPointActor* WayPointActor;
	
	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* FXCursor;
	
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
	// FVector TargetLocation;
	
	UPROPERTY(BlueprintReadWrite)
	FVector2D InitialMousePosition;
	
	//NewMousePos
	UPROPERTY(BlueprintReadWrite)
	FVector2D NewMousePosition;

	FVector2D STEdge1;
	FVector2D STEdge2;

	UPROPERTY(BlueprintReadWrite)
	bool CursorMoved = false;


	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObjectsInContainer
	TArray<AActor*> ActorsInSelection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDecalSelect = false;

	bool SelectionProcessed = false;



protected:

	bool CanMove = false;
	
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

	UBlackboardComponent* BlackboardComponent;
	
private:
	
	float TargetZoom = 3000.f;
	float ZoomSpeed = 2.f;
	
	// Susceptible to Change
	int32 MaxZoom = 4000.f;
	int32 MinZoom = 500.f;

	float ZoomRate = 30;
	float MouseDownTime;
	float Dist;

	
public:
	
	void EventKey();
	UFUNCTION(BlueprintCallable)
	void StartBoxSelection();
	UFUNCTION(BlueprintCallable)
	void EndBoxSelection();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

	UPROPERTY(EditAnywhere)
	AGenericBaseAI* Decals;

	bool bNotHit;

	// What happens when pawn selected
	UFUNCTION(BlueprintCallable)
	void HandlePawnSelection(APawn* HitPawn);

	// Logic for the Units decal apearing and disapearing
	void UnitDecals(AGenericBaseAI* HitPawn);

	void CleanUpDecal(APawn* HitPawn);

	void REvent_PlayDecal(const FVector& Location);
	// Updates the Marquee edges
	UFUNCTION(BlueprintCallable)
	void UpdateFlow();
	
	FHitResult bHit; 
	
};
