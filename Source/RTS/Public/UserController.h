// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "NiagaraSystem.h"
#include "UserCharacter.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Economy/EconomyManager.h"
#include "Engine/DecalActor.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/SelectionInterface.h"
#include "UserController.generated.h"


class IBuildingInterface;
class ICombatInterface;
class UDecalComponent;
class UBoxComponent;


/**
 * 
 */
UCLASS()
class RTS_API AUserController : public APlayerController, public ICombatInterface
{
	GENERATED_BODY()

public:
	UEconomyManager* EconomyManager = nullptr;

	// Widget for the User Interface //

	// The Widget Class for the User Interface. 
	UClass* WidgetClass;

	// Instance of the Widget Class.
	UUserWidget* ResourceWidgetInstance;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetUnits")
	TArray<AGenericBaseAI*> GrabAllUnits;
	
	// --
	
	
	int32 AllUnitAmountInt (TArray<AGenericBaseAI*> AllU);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetUnits")
	int32 AllWorldUnitsINT32;

	UFUNCTION(BlueprintCallable, Category = "GetUnits")
	TArray<AActor*> GetSelectedUnitsBP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetUnits")
	bool SetAllUnitsTrue = false;

	// --------------------------------
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
	void MoveDronesToGatherPos(FVector GatherPos, AActor* Drone);
	
	void StartBoxSelection(); // User Input to select Actor
	void EndBoxSelection(); // End of User Input
	void MultiSelect(); // User Input With intent of Selection Multiple Units
	bool HasCursorMoved();

	
	void CastToActor(); // Raycasts to Actors to check Hit Result
	void HandleSelection(AActor* ActorHit);// Determines On how the Actor will be processed.
	
	
	//TArray<AActor*> ConvertPawnArrayToActorArray(const TArray<APawn*>& PawnArray); // Converts Pawn Array to Actor Array
	
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
	
	// Combat Interface that stores important Data for the Combat;
	ICombatInterface* CombatInterface;
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller")
	TWeakObjectPtr<AUserController> UserControllerPtr;
	
	
	
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

	// Economy --

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int UWoodAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int UStoneAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int UFoodAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int UGoldAmount;

	UFUNCTION(BlueprintCallable)
	void OnWoodChanged(int32 NewAmount) { UWoodAmount = NewAmount; };
	UFUNCTION(BlueprintCallable)
	void OnStoneChanged(int32 NewAmount) { UStoneAmount = NewAmount; };
	UFUNCTION(BlueprintCallable)
	void OnFoodChanged(int32 NewAmount) { UFoodAmount = NewAmount; };
	UFUNCTION(BlueprintCallable)
	void OnGoldChanged(int32 NewAmount) { UGoldAmount = NewAmount; };

	// ------------
	void UpdateResources();
	
	// Checks if we are selecting multiple ai
	bool MultiselectCond;

	// Checks if specific class has been raycasted too.
	bool bNotHit;

	// Logic for the Units decal apearing and disapearing
	void UnitDecals(AGenericBaseAI* HitPawn);

	// Bind Key "P" to Patrol Mode
	void EnterPatrolMode();

	void ProcessPatrolClick(FHitResult HitResult);
	void AddBuildingWidgetToScreen(UUserWidget* BuildingWidget);

	// Checks if the AI is in Patrol Mode.
	bool bPatrolMode;
	// The Patrol Points for the AI to move to.
	TArray<FVector> PatrolPoints;
	// The Current Patrol Point the AI is moving to.
	TArray<AGenericBaseAI*> PatrolUnits;

	
	FHitResult bHit; 

	void InitializeCombatInterface(AActor* InitActor);
	
};
