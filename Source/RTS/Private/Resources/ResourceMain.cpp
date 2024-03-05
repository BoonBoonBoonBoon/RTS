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


void AResourceMain::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if(OtherActor && OverlappedComponent->IsOverlappingActor(OtherActor))
	{
		if(!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				--TimeValue;
				if (TimeValue <= 0)
				{
					++TimeValue;
					RInterface->ResourceAmount(this, OtherActor, FVector(0), SweepResult);
				}
			}, TimeValue, true);
		}
	}
}

void AResourceMain::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End overlap"));
	if(OtherActor && !OverlappedComponent->IsOverlappingActor(OtherActor))
	{
	
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void AResourceMain::SetResourceTimer()
{
	/*GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		--TimeValue;
		if (TimeValue <= 0)
		{
			RInterface->ResourceAmount(this, OtherActor, FVector(0), SweepResult);
			TimeValue = 1; // Reset TimeValue for next iteration
		}
	}, 1.0f, true);*/
}


int32 AResourceMain::GetAmount()
{
	return 0;
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

