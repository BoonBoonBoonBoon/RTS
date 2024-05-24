// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"

#include "NavigationSystem.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseEnemy/GenericEnemyController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "RTS/RTSGameModeBase.h"



// Sets default values
AGenericBaseEnemyAI::AGenericBaseEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	// Initialize health attributes
	Health = 50.f;
	MaxHealth = 100.f;
	HealthRegenRate = 5.f;
	
	// Set the AI Controller class
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AGenericEnemyController::StaticClass();


	// Initialize the AttackRangeSphere
	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeSphere->InitSphereRadius(500.0f); // Set this to the desired attack range
	AttackRangeSphere->SetupAttachment(RootComponent);

	// Set up the overlap event
	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AGenericBaseEnemyAI::OnOverlapBegin);
	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AGenericBaseEnemyAI::OnOverlapEnd);
	
}

void AGenericBaseEnemyAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Declare the variable
	float Dmg = 20.0f; // Set this to the desired damage amount

	// Check if the overlapped actor is a worker drone
	if (OtherActor == Cast<AGenericBaseAI>(OtherActor))
	{

		if (TimeValue <= 0)
		{
			TimeValue = 2;
		}

		// Check if the timer is already set
		if (!this->GetWorld()->GetTimerManager().IsTimerActive(AttackTimerHandleLightInf))
		{
			// lambda function, Set a timer to call the AttackEnemy function every 2 seconds
			this->GetWorld()->GetTimerManager().SetTimer(AttackTimerHandleLightInf, [this, OtherActor, Dmg]()
			{
				TimeValue--;

				if (TimeValue <= 0)
				{
					if (AGenericBaseAI* Enemy = Cast<AGenericBaseAI>(OtherActor))
					{
						Enemy->UnitDataMap[Enemy->UnitType].UnitStats.Health -= Dmg;
						
						// Check if the enemy's health is zero or less
						if (Enemy->UnitDataMap[Enemy->UnitType].UnitStats.Health <= 0)
						{
							// Clear the timer if the enemy's health is zero or less
							this->GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandleLightInf);
							Enemy->Des();
						}
						else
						{
							// Reset the timer if the enemy is still alive
							TimeValue = 2;
						}
					}
				}
			}, 2, true);
		}
	}
}


void AGenericBaseEnemyAI::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapped actor is a worker drone
	if (OtherActor->ActorHasTag("Friendly"))
	{
	}
}

// Called when the game starts or when spawned
void AGenericBaseEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Enemy");
	
	GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
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

	if (Health <= 0)
	{
		Destroy();
		if (GameMode)
		{
			GameMode->CheckEnemies();
		}
	}
}

void AGenericBaseEnemyAI::RegenerateHealth(float DeltaTime)
{
	// Increase health by the regeneration rate per second
	Health += HealthRegenRate * DeltaTime;

	// Clamp health between 0 and MaxHealth
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

