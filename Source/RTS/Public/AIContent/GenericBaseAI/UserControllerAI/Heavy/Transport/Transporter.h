// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TransportAttributesComponent.h"
#include "AIContent/GenericBaseAI/GenericBaseAI.h"
#include "Transporter.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ATransporter : public AGenericBaseAI
{
	GENERATED_BODY()
	UTransportAttributesComponent* TransportAttributesComponent;

	ATransporter();

	virtual void BeginPlay() override;
};
