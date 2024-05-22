// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"

#include "NavigationSystem.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "AIContent/GenericBaseEnemy/GenericEnemyController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Attacking"));
	// Declare the variable
	float Dmg = 10.0f; // Set this to the desired damage amount

	// Check if the overlapped actor is a worker drone
	if (OtherActor == Cast<AGenericBaseAI>(OtherActor))
	{
		// Start damaging the worker drone
		UE_LOG(LogTemp, Warning, TEXT("Damaging worker drone..."));

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

				UE_LOG(LogTemp, Warning, TEXT("Remaining time for timer: %d"), TimeValue);

				if (TimeValue <= 0)
				{
					if (AGenericBaseAI* Enemy = Cast<AGenericBaseAI>(OtherActor))
					{
						Enemy->TakeDamage(Dmg);

						if (Enemy->UnitDataMap[Enemy->UnitType].UnitStats.Health <= 0)
						{
							this->GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandleLightInf);
						}
					}
				}
			}, 2, true);
		}
	}
}

/*
void AGenericBaseEnemyAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapped actor is a worker drone
	if (OtherActor->ActorHasTag("Friendly"))
	{
		// Start damaging the worker drone
		// Replace this with your actual damage logic
		UE_LOG(LogTemp, Warning, TEXT("Damaging worker drone..."));

		// Get Overlapped actor and call TakeDamage function
		
		//OtherActor->TakeDamage(15);


		if (TimeValue <= 0)
		{
			TimeValue = 2;
		}
    
		// Check if the timer is already set
		if (!this->GetWorld()->GetTimerManager().IsTimerActive(this->AttackTimerHandleLightInf))
		{
			// lambda function, Set a timer to call the AttackEnemy function every 2 seconds
			this->GetWorld()->GetTimerManager().SetTimer(this->AttackTimerHandleLightInf, [this, this, OtherActor, Dmg]()
			{
				TimeValue--;

				UE_LOG(LogTemp, Warning, TEXT("Remaining time for timer: %d"), TimeValue);

				if (TimeValue <= 0)
				{
					//TimeValue = Unit->UnitDataMap[Unit->UnitType].UnitStats.AttackSpeed;
					if (AGenericBaseAI* Enemy = Cast<AGenericBaseAI>(OtherActor))
					{
						Enemy->TakeDamage(Dmg);
                        
						//if (Enemy->Health <= 0)
						if(Enemy->UnitDataMap[Enemy->UnitType].UnitStats.Health <= 0)
						{
							this->GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandleLightInf);
							//Unit->GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandleLightInf);
						}
					}
				}
			}, 2, true);
		}
	}
}
*/


void AGenericBaseEnemyAI::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapped actor is a worker drone
	if (OtherActor->ActorHasTag("Friendly"))
	{
		// Stop damaging the worker drone
		// Replace this with your actual stop attack logic
		UE_LOG(LogTemp, Warning, TEXT("Stopped damaging worker drone..."));
	}
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

