// Fill out your copyright notice in the Description page of Project Settings.


#include "AIContent/GenericBaseEnemy/GenericBaseEnemyAI.h"

// Sets default values
AGenericBaseEnemyAI::AGenericBaseEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenericBaseEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenericBaseEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGenericBaseEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

