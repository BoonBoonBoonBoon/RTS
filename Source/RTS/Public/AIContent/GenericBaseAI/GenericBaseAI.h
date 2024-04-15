// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorAttributesComponent.h"
#include "AIController.h"
#include "GenericController.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/SelectionInterface.h"
#include "GenericBaseAI.generated.h"


class AUserController; 

UCLASS()
class RTS_API AGenericBaseAI : public ACharacter, public ISelectionInterface, public ICombatInterface
{
	GENERATED_BODY()

	// Used as a generator for the pawn to emit a stimuli. Need this as the AI will use this as a tool to percept.
	class UAIPerceptionStimuliSourceComponent* StimuliSourcePredator;

	UPROPERTY()
	UActorAttributesComponent* ActorAttributesComponent;
	
public:
	// Sets default values for this character's properties
	AGenericBaseAI();

	// UNIT DATA ------------

	// Container to store the Attribute & Stats of the unit.
	UPROPERTY(EditAnywhere, Category = "Unit Data")
	FUnitData UnitData;

	// Container to store the type of unit.
	UPROPERTY(EditAnywhere, Category = "Unit Type")
	EUnitTypes UnitType;

	// TMap to store the data of the unit types amd their stats. 
	UPROPERTY(EditAnywhere, Category = "Tmap Unit Data")
	TMap<EUnitTypes, FUnitData> UnitDataMap;
	
	// ----------------------
	
	ISelectionInterface* SelectionInterface;

	ICombatInterface* CombatInterface;
	
	// EQS Query asset 
	UPROPERTY()
	UEnvQuery* MyQuery;

	// struct, which is used to execute the EQS query. 
	FEnvQueryRequest MyQueryRequest;

	void MyQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectedDecalComp;

	UPROPERTY(EditAnywhere)
	AGenericController* Con;

	// MOVEMENT ------------
	
	// Takes in the vector where we want to move to 
	mutable FVector LocationToMove;
	// Checks if the vector is valid
	mutable bool ValidHit;
	void MovePTR();

	// ----------------------

	// PATROL POINTS ------------

	// Sets the patrol points for the AI to move to.
	void SetPatrolPoints(FVector PointA, FVector PointB);
	
	// --------------------------

	bool DecalHit = false;

	AAIController* GetAIController(AGenericBaseAI* Actor);
	
	// COMBAT -------------------
	
	/*
	virtual FVector FoundEnemyLocation() override;
	virtual bool MoveToEnemy() override;
	virtual void AttackEnemy() override;

	float AttackRange = 100.f;*/
	// --------------------------

private:
	AActor* TargetEnemy = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void SetupStimulusSource();

public:

	void GatherAroundEnemy(FVector& Destination);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
