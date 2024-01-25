// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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

	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectedDecalComp;

	UPROPERTY(EditAnywhere)
	AUserController* UserController;
	
	bool DecalHit = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void SetupStimulusSource();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
