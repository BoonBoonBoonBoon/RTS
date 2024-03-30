// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "NiagaraSystem.h"
#include "UserCharacter.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Engine/DecalActor.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/SelectionInterface.h"
#include "UserController.generated.h"


class IBuildingInterface;
//class EBuildingTypes;
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
	
	
	void EventKey(); // Movement and Attack Direction
	void HandleResourceGathering(AActor* Resource);
	
	void StartBoxSelection(); // User Input to select Actor
	void EndBoxSelection(); // End of User Input
	void MultiSelect(); // User Input With intent of Selection Multiple Units
	bool HasCursorMoved();

	
	void CastToActor(); // Raycasts to Actors to check Hit Result
	void HandleSelection(AActor* ActorHit);// Determines On how the Actor will be processed.
	
	
	TArray<AActor*> ConvertPawnArrayToActorArray(const TArray<APawn*>& PawnArray); // Converts Pawn Array to Actor Array
	
	void HandleMarqueePawnSelection(AActor* HitPawn); // Selects Actors Hit by Tool
	void UpdateFlow(); // Draws Marquee Selection Tool 
	
protected:
	
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
	
	// Building Interface that stores important Data for the building;
	IBuildingInterface * BuildingInterface;

	// Selection Interface that stores important Data for the Unit selection;
	ISelectionInterface* SelectionInterface;
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

	// Stores the building type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SelectedBuilding;
	
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
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	// Checks if we are selecting multiple ai
	bool MultiselectCond;

	// Checks if specific class has been raycasted too.
	bool bNotHit;

	// Logic for the Units decal apearing and disapearing
	void UnitDecals(AGenericBaseAI* HitPawn);
	
	FHitResult bHit; 
	
};
