// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericBaseAI.h"

#include "UserController.h"
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

	
	/*// Spawn the AI controller
	AGenericBaseAIController* NewAIController = GetWorld()->SpawnActor<AGenericBaseAIController>(AGenericBaseAIController::StaticClass());

	// Assign the AI controller to the actor
	if (NewAIController)
	{
		AController* C = Cast<AController>(NewAIController);
		if (C)
		{
			C->Possess(this);
		}
	}*/
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

// Called every frame
void AGenericBaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("GenControler>(GetController());"));
	AGenericBaseAIController* ControllerAI = Cast<AGenericBaseAIController>(GetController());
	if(ControllerAI)
	{
		UE_LOG(LogTemp, Warning, TEXT("GenControllerAGenericBaseAIController* ControllerAI = Cast<AGenericBaseAIController>(GetController());"));
	}

	
}

// Called to bind functionality to input
void AGenericBaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

