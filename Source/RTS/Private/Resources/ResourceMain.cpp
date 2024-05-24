// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceMain.h"

#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Components/BoxComponent.h"



// Sets default values
AResourceMain::AResourceMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Resource");
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AResourceMain::BeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AResourceMain::EndOverlap);
}


EResourceType AResourceMain::GetResourceType() const
{
	return EResourceType::Invalid;
}


void AResourceMain::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	// If the actor is valid and is overlapping the component, set a timer for the actor.
	if (OtherActor && OverlappedComponent->IsOverlappingActor(OtherActor))
	{
		if (!OtherActor->IsA(AGenericBaseAI::StaticClass()))
		{
			return; // Early return if OtherActor is not a valid type
		}
		
		FTimerHandle& ActorTimer = ActorTimers[OtherActor]; // Get the timer for the actor.
		GetWorld()->GetTimerManager().SetTimer(ActorTimer, [this, OtherActor, SweepResult]()
		{
			--TimeValue;
			if (TimeValue == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Timer Reached Zero :: ResourceMain :: BeginOverlap"));
				++TimeValue;
				RInterface->TakeResourceObject(this, OtherActor, FVector(0), SweepResult);
			}
		}, TimeValue, true);
	}
}

void AResourceMain::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// If the actor is in the map, clear the timer and remove the actor from the map.
	if(OtherActor && ActorTimers.find(OtherActor) != ActorTimers.end())
	{
		FTimerHandle ActorTimer = ActorTimers[OtherActor];
		GetWorld()->GetTimerManager().ClearTimer(ActorTimer);
		ActorTimers.erase(OtherActor);
	}
}

int32 AResourceMain::GetAmount()
{
	return{};
}

int32 AResourceMain::TakeResources(int32 amount)
{
	return {};
}

// Called when the game starts or when spawned
void AResourceMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourceMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//ResourceTimer();
}

