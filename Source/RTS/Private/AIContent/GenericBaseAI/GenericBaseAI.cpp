// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "UserController.h"
#include "AIContent/GenericBaseAI/GenericController.h"
#include "Components/DecalComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

class AUserController; 

// Sets default values
AGenericBaseAI::AGenericBaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SelectedDecalComp = CreateDefaultSubobject<UDecalComponent>("Decal");
	SelectedDecalComp->SetupAttachment(RootComponent);
	
	// Set Tag to building
	Tags.Add("Unit");
	
	
}

void AGenericBaseAI::MyQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
}

void AGenericBaseAI::MovePTR()
{
	if(ValidHit)
	{
		if(AController* CTRL = GetController()){
			if(AGenericController* C = Cast<AGenericController>(CTRL))
			{
				C->CheckValid = true;
				C->MoveLoc = LocationToMove;
				// Log the name of the controller
				UE_LOG(LogTemp, Warning, TEXT("Current Controller Name: %s"), *C->GetName());
				ValidHit = false;
			}else {
				
				UE_LOG(LogTemp, Warning, TEXT("AGenericController* C = Cast<AGenericController>(CTRL) Failed"));
			}
		}
	}
}

AAIController* AGenericBaseAI::GetAIController(AGenericBaseAI* Actor)
{
	return Cast<AAIController>(Actor->GetController());
}

// Called when the game starts or when spawned
void AGenericBaseAI::BeginPlay()
{
	Super::BeginPlay();
	SelectedDecalComp->SetVisibility(false);
	
}


void AGenericBaseAI::SetupStimulusSource()
{
	StimuliSourcePredator = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSourcePredator)
	{
		StimuliSourcePredator->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourcePredator->RegisterWithPerceptionSystem();
	}
}

void AGenericBaseAI::MoveToDes(FVector& Destination)
{
	// Print the hit location coordinates to the output log
	UE_LOG(LogTemp, Warning, TEXT("Hit Location: X=%f, Y=%f, Z=%f"), Destination.X, Destination.Y, Destination.Z);
	//Con->MoveToLocation(Destination);
	
	
}

// Called every frame
void AGenericBaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ValidHit)
	{
		MovePTR();
	}
	

	

	
	// Get the AI controller
	/*AGenericController* MyAIController = Cast<AGenericController>(GetController());
	if (!MyAIController)
	{
		// If the AI controller is null, create a new one and possess the AI character
		MyAIController = GetWorld()->SpawnActor<AGenericController>(AGenericController::StaticClass());
		
		if (MyAIController)
		{
			// Possess the AI character with the new AI controller
			MyAIController->Possess(this);
		}else
		{
			// Log an error or handle the case where the AI controller creation failed
			UE_LOG(LogTemp, Error, TEXT("Failed to create GenericController"));
		}
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Cast Failed"));
		// The AI is already possessed by a controller
		// You can perform actions using the existing AI controller
		// For example, move to a location
		//FVector DestinationLocation(1000.0f, 0.0f, 0.0f);
		//MyAIController->MoveToLocation(DestinationLocation);
	}*/
}

// Called to bind functionality to input
void AGenericBaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

