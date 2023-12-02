// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UserController.generated.h"


class UDecalComponent;
class UBoxComponent;
class AUserCharacter;


/**
 * 
 */
UCLASS()
class RTS_API AUserController : public APlayerController
{
	GENERATED_BODY()

	AUserController();
	
};
