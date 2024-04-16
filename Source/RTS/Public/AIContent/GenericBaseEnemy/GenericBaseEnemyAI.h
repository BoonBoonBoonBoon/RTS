// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericBaseEnemyAI.generated.h"


UCLASS()
class RTS_API AGenericBaseEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGenericBaseEnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	// Health attribute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	// Maximum health attribute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	// Health regeneration rate per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float TimeSinceLastDamage;

	bool bIsGettingHealing; // When the AI is reciving healing from a building or ai
	
	// Method for taking damage
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	// Method for regenerating health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void RegenerateHealth(float DeltaTime);
	
};
