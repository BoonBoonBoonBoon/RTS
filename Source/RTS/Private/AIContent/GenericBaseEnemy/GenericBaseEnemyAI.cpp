// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"

// Sets default values
AGenericBaseEnemyAI::AGenericBaseEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the CombatInterface
	//CombatInterface = Cast<ICombatInterface>(this);
	
	// Initialize health attributes
	Health = 50.f;
	MaxHealth = 100.f;
	HealthRegenRate = 5.f;
}

// Called when the game starts or when spawned
void AGenericBaseEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Enemy");
}

// Called every frame
void AGenericBaseEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Increase the timer
	TimeSinceLastDamage += DeltaTime;

	// Regenerate health over time if it has been more than 5 seconds since the last damage was taken
	if (TimeSinceLastDamage >= 5.f)
	{
		RegenerateHealth(DeltaTime);
	}
	else if (bIsGettingHealing)
	{
		RegenerateHealth(DeltaTime);
	}
}


void AGenericBaseEnemyAI::TakeDamage(float DamageAmount)
{
	// Reduce health by the damage amount
	Health -= DamageAmount;
	
	// Log the health
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	// Clamp health between 0 and MaxHealth
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	
	// Reset the timer
	TimeSinceLastDamage = 0.f;

	if(Health <= 0)
	{
		Destroy();
	}
}

void AGenericBaseEnemyAI::RegenerateHealth(float DeltaTime)
{
	// Increase health by the regeneration rate per second
	Health += HealthRegenRate * DeltaTime;

	// Clamp health between 0 and MaxHealth
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

