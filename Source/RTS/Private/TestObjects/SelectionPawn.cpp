// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObjects/SelectionPawn.h"

#include "UserController.h"
#include "Chaos/AABBTree.h"

// Sets default values
ASelectionPawn::ASelectionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CollisionRoot->OnComponentBeginOverlap.AddDynamic(this, &ASelectionPawn::OverlapBegin);
	
	CollisionRoot = CreateDefaultSubobject<USphereComponent>("CollisionRoot ");
	CollisionRoot->SetupAttachment(RootComponent);
}

void ASelectionPawn::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	// Do something when hit
	UE_LOG(LogTemp, Warning, TEXT("Actor %s 11111111!"), *GetName());
}

void ASelectionPawn::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUserController* UserController = Cast<AUserController>(OtherActor);
	if(UserController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s 11111111!"), *GetName());
	}
}

void ASelectionPawn::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void ASelectionPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CollisionRoot->OnComponentBeginOverlap.AddDynamic(this, &ASelectionPawn::OverlapBegin);
}

// Called to bind functionality to input
void ASelectionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

