// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorAttributesComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTS_API UActorAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActorAttributesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Worker Drone
	bool bCanGather;
	bool bCanRepair;

	// Military Units.
	bool bCanAttack;
	bool bCanGuard;
	bool bCanPatrol;
	bool bCanRange;

	// Special Units.
	bool bCanSearch;
	bool bCanTransport;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// Worker Drone.
	virtual void SetCanGather(bool bNewCanGather);
	virtual bool CanGather() const;

	virtual void SetCanRepair(bool bNewCanRepair);
	virtual bool CanRepair() const;

	virtual void SetCanAttack(bool bNewCanAttack);
	virtual bool CanAttack() const;

	virtual void SetCanGuard(bool bNewCanGuard);
	virtual bool CanGuard() const;

	virtual void SetCanPatrol(bool bNewCanPatrol);
	virtual bool CanPatrol() const;

	virtual void SetCanRange(bool bNewCanRange);
	virtual bool CanRange() const;

	virtual void SetCanSearch(bool bNewCanSearch);
	virtual bool CanSearch() const;

	virtual void SetCanTransport(bool bNewCanTransport);
	virtual bool CanTransport() const;
};
