// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceMain.h"
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

// To send resoucres we do a function thats called everytick and we say a certain timer
// which lets the AI pickup 1 resource at a time EACH. and it repeats still a second is up so it can grab another resource.

// can give them inventory by making stuct invetory then saying "inventory new AiInv = IncomingInt;"
// then we can say "AiInv.Amount += 1;" and then we can say "IncomingInt = AiInv;" to send it back to the AI.


EResourceType AResourceMain::GetResourceType() const
{
	return EResourceType::Invalid;
}

/* TODO:
 * 1. Create a Child Of genericAI, whose purpose it is to gather resources.
 * 2. Create Optional Upgrades for the AI to gather resources faster. (Check if the AI has the upgrade, if so, gather resources faster.) (Use Struct)
 * 3. Check for Upgrades.
 * 4. Upgrades then determine the amount we can take from the resource. (Increase Speed even?) (maybe Nerf Speed)
 * (Give the AI a value Variable in which it increases pickup speed by a percentile amount)
 * ie. Reducing the timer gradually -> then to buy the upgrades the ai need to have a certain amount of resources.
 * Check out FResourceStats For the amount we should take.
 */

void AResourceMain::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	// If the actor is valid and is overlapping the component, set a timer for the actor.
	if (OtherActor && OverlappedComponent->IsOverlappingActor(OtherActor))
	{
		FTimerHandle& ActorTimer = ActorTimers[OtherActor]; // Get the timer for the actor.
		GetWorld()->GetTimerManager().SetTimer(ActorTimer, [this, OtherActor, SweepResult]()
		{
			--TimeValue;
			if (TimeValue <= 0)
			{
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

