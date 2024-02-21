// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "NiagaraSystem.h"
#include "UserCharacter.h"
#include "Enums/EnumsDatabase.h"
#include "Interfaces\BuildingInterface.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DecalActor.h"
#include "EQS/WayPointActor.h"
#include "GameFramework/PlayerController.h"
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

public:
	
	AUserController();
	virtual void OnPossess(APawn* InPawn) override;

	// Camera Movement Edge of Screen
	void EdgeScrolling();
	void EdgeScrolling_WASD_Up(float Value);
	void EdgeScrolling_WASD_Down(float Value); 
	void EdgeScrolling_WASD_Right(float Value); 
	void EdgeScrolling_WASD_Left(float Value); 
	
	void MoveCamera(const FVector& Direction);
	
	void CursorToWidget();
	void EventKey(); // Movement and Attack Direction

	
	void StartBoxSelection(); // User Input to select Actor
	void EndBoxSelection(); // End of User Input
	void MultiSelect(); // User Input With intent of Selection Multiple Units
	bool HasCursorMoved(); 
	
	void UnitSelection(); // Raycasts to Actors to check Hit Result
	void HandlePawnSelection(APawn* HitPawn);
	
	void HandleMarqueePawnSelection(AActor* HitPawn); // Selects Actors Hit by Tool
	void UpdateFlow(); // Draws Marquee Selection Tool 


protected:
	// Building Interface that stores important Data for the building

	IBuildingInterface* BuildingInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere)
	AGenericBaseAI* GenericBaseAI;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* SelectionArea;
	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	UBlackboardComponent* BlackboardComponent; // ? maybe delete
	
	UPROPERTY(EditAnywhere)
	AGenericBaseAI* Decals;
	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	AUserCharacter* UserCharacter;

	// Checks What the type of building a pawn is
	EBuildingTypes* BuildingType;
	
public:

	

	UPROPERTY(BlueprintReadWrite)
	FVector2D InitialMousePosition; // 2D World Space Current Mouse Position
	
	FVector2D MousePosition;
	
	UPROPERTY(BlueprintReadWrite)
	FVector2D NewMousePosition;
	
	UPROPERTY(BlueprintReadWrite)
	bool CursorMoved = false;
	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObjectsInContainer
	TArray<AActor*> ActorsInSelection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDecalSelect = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SelectedUnits;

protected:
	
	float dist;
	FVector SelectionSize; 
	FVector CenterMouseLocation;
	FVector MouseStart;
	FVector MouseEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Selection")
	bool bIsSelecting;
	
	bool bCheckCursor;
	bool bCursorMove;
	
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	// Checks if we are selecting multiple ai
	bool MultiselectCond;
	
	bool bNotHit;
	
	// Logic for the Units decal apearing and disapearing
	void UnitDecals(AGenericBaseAI* HitPawn);
	
	FHitResult bHit; 
	
};
