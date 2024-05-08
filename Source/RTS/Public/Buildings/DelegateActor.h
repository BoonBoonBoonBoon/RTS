// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenB, bool, bOpenBarracksUI);

UCLASS()
class RTS_API ADelegateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateActor();

	UPROPERTY(BlueprintAssignable)
	FOpenB OpenUIB;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
