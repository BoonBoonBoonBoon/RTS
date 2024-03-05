// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ResourceInterface.h"
#include "ResourceMain.generated.h"

UCLASS()
class RTS_API AResourceMain : public AActor, public IResourceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceMain();

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionComp;
	
	IResourceInterface* RInterface;
	virtual EResourceType GetResourceType() const ;

	FTimerHandle TimerHandle;
	
	// Called when this actor begins to overlap another actor
	UFUNCTION( )
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult );

	int32 TimeValue = 1; // The time it takes for the AI to take the resource.
	
	// Returns the amount of resource.
	virtual int32 GetAmount();
	
	// AI takes The Resources.
	//virtual void TakeResources(int32 amount);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
	
// Handles the collision.
//void ObjectHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	