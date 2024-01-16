// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseAI/GenericBaseAI.h"

#include "UserController.h"
#include "Components/DecalComponent.h"

// Sets default values
AGenericBaseAI::AGenericBaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectedDecalComp = CreateDefaultSubobject<UDecalComponent>("Decal");
	SelectedDecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGenericBaseAI::BeginPlay()
{
	Super::BeginPlay();
	UserController = Cast<AUserController>(GetWorld()->GetFirstPlayerController());
	
}

// Called every frame
void AGenericBaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	
	if (UserController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Visible"));
	}
	
}

// Called to bind functionality to input
void AGenericBaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

