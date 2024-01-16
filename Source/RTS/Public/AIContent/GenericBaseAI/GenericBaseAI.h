// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserController.h"
#include "GameFramework/Character.h"
#include "GenericBaseAI.generated.h"

UCLASS()
class RTS_API AGenericBaseAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGenericBaseAI();

	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectedDecalComp;

	UPROPERTY(EditAnywhere)
	AUserController* UserController;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
