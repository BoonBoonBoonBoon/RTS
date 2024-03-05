// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericController.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/Character.h"
#include "GenericBaseAI.generated.h"

class AUserController; 

UCLASS()
class RTS_API AGenericBaseAI : public ACharacter
{
	GENERATED_BODY()

	// Used as a generator for the pawn to emit a stimuli. Need this as the AI will use this as a tool to percept.
	class UAIPerceptionStimuliSourceComponent* StimuliSourcePredator;
	
public:
	// Sets default values for this character's properties
	AGenericBaseAI();


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

	// Takes in the vector where we want to move to 
	mutable FVector LocationToMove;
	// Checks if the vector is valid
	mutable bool ValidHit;
	void MovePTR();
	
	bool DecalHit = false;

	AAIController* GetAIController(AGenericBaseAI* Actor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void SetupStimulusSource();

public:

	void MoveToDes(FVector& Destination);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
