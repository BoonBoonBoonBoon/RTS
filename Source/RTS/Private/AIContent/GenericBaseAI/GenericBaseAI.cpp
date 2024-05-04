// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "UserController.h"
#include "AIContent/GenericBaseAI/GenericController.h"
#include "Components/DecalComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

class AUserController; 

// Sets default values
AGenericBaseAI::AGenericBaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorAttributesComponent = CreateDefaultSubobject<UActorAttributesComponent>(TEXT("ActorAttributesComponent"));
	
	SelectedDecalComp = CreateDefaultSubobject<UDecalComponent>("Decal");
	SelectedDecalComp->SetupAttachment(RootComponent);

	// Initialize the Stimulus Source
    SetupStimulusSource();
	
	// Initialize the Perception System
	//InitializePerceptionSystem();
	
	// Set Tag to building
	Tags.Add("Unit");
		
	// Set the TeamId
	//TeamId = 11;
	
}

void AGenericBaseAI::MyQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
}

/**
 * @brief Moves the AI to a specific location if a valid hit is detected.
 *
 * This function checks if a valid hit is detected. If so, it gets the controller of the AI and casts it to a GenericController.
 * It then sets the CheckValid flag to true and sets the MoveLoc to the location to move to. It also logs a warning message indicating that the function was called.
 * Finally, it sets the ValidHit flag to false.
 */
void AGenericBaseAI::MovePTR()
{
	if(ValidHit)
	{
		if(AController* Ctrl = GetController()){
			if(AGenericController* C = Cast<AGenericController>(Ctrl))
			{
				C->CheckValid = true;
				C->MoveLoc = LocationToMove;

				UE_LOG(LogTemp, Warning, TEXT("MovePTR() Called"));
				ValidHit = false;
			}
		}
	}
}

/**
 * @brief Sets the patrol points for the AI.
 *
 * This function gets the controller of the AI and casts it to a GenericController. It then sets the PatrolPointA and PatrolPointB to the given points and sets the bIsPatrolling flag to true.
 * It also checks if the controller can be cast to a UserController. If so, it sets the bPatrolMode flag to false and empties the PatrolPoints array.
 *
 * @param PointA The first patrol point.
 * @param PointB The second patrol point.
 */
void AGenericBaseAI::SetPatrolPoints(FVector PointA, FVector PointB)
{

	// Use AIController to move to the next point
	AGenericController* AIController = Cast<AGenericController>(GetController());
	if (AIController)
	{
		AIController->PatrolPointA = PointA;
		AIController->PatrolPointB = PointB;
		AIController->bIsPatrolling = true;

		// Clear Out the patrol elements.
		if (AUserController* PController = Cast<AUserController>(GetController()))
		{
			PController->bPatrolMode=false;
			PController->PatrolPoints.Empty();
		}
	}
}

/**
 * @brief Gets the AI controller of the given actor.
 *
 * This function gets the controller of the given actor and casts it to an AIController.
 *
 * @param Actor The actor to get the AI controller of.
 * @return The AI controller of the given actor.
 */
AAIController* AGenericBaseAI::GetAIController(AGenericBaseAI* Actor)
{
	return Cast<AAIController>(Actor->GetController());
}



// Called when the game starts or when spawned
void AGenericBaseAI::BeginPlay()
{
	Super::BeginPlay();
	
	SelectedDecalComp->SetVisibility(false);
	
	// Cast this to ISelectionInterface
	SelectionInterface = Cast<ISelectionInterface>(this);

	// Initialize the CombatInterface
	CombatInterface = Cast<ICombatInterface>(this);


}


void AGenericBaseAI::SetupStimulusSource()
{
	StimuliSourceAi = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSourceAi)
	{
		StimuliSourceAi->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourceAi->RegisterWithPerceptionSystem();
	}
}


// Called every frame
void AGenericBaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(bUnitFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttackingUnits: %d"), AttackingUnits.Num());
		
		for (AActor* Src: AttackingUnits)
		{
			if(auto Unit = Cast<AGenericBaseAI>(Src))
			{
				FUnitData unitData = Unit->UnitDataMap[Unit->UnitType];
		
				if (unitData.Attributes.Contains(EUnitAttributes::Attack))
				{
					// Calculate the distance between the AI and the target
					float distance = FVector::Dist(Unit->GetActorLocation(), CurrentEnemy);
					UE_LOG(LogTemp, Warning, TEXT("distance: %f"), distance);

			
					// Check if the AI is within a certain distance
					if (distance <= 300.f)
					{
						// Set isAttacking to true for the individual instance of the actor
						unitData.UnitStats.bIsAttacking = true;
						//InitiateCombat(unitData.UnitStats.bIsAttacking, Unit);
						UE_LOG(LogTemp, Warning, TEXT(" Attacking1"));
					}
					else
					{
						// Set isAttacking to false for the individual instance of the actor
						unitData.UnitStats.bIsAttacking = false;
						//InitiateCombat(unitData.UnitStats.bIsAttacking, Unit);
						//UE_LOG(LogTemp, Warning, TEXT("Not Attacking"));
					}
				}
			}
		}
	} else
	{
	//	UE_LOG(LogTemp, Warning, TEXT("AttackingUnits Not Attacjubg: %d"), AttackingUnits.Num());
	}
	
	if(ValidHit)
	{
		MovePTR();
	}
}

void AGenericBaseAI::InitiateCombat(bool bIsAttacking, AGenericBaseAI* Unit)
{
	
	if (bIsAttacking)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get World"));
		GetWorld()->GetTimerManager().SetTimer(Unit->AttackTimerHandle, this, &AGenericBaseAI::TimerCallback, TimeValue, true);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("attack false "));
	}
}

// Add a new member function to the ICombatInterface class
void AGenericBaseAI::TimerCallback()
{
	--TimeValue;
	UE_LOG(LogTemp, Warning, TEXT("TimeValue: %f"), TimeValue);
	
	if (TimeValue <= 0)
	{
		++TimeValue;
		AttackEnemy();
	}
}











// Called to bind functionality to input
void AGenericBaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
