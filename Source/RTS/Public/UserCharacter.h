// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UserCharacter.generated.h"

UCLASS()
class RTS_API AUserCharacter : public ACharacter
{
	GENERATED_BODY()


/////////////////// OVERSEER /////////////////////


	
public:
	// Sets default values for this character's properties
	AUserCharacter();

	float TargetZoom = 3000.f;
	float ZoomSpeed = 2.f;
	
	// Susceptible to Change
	int32 MaxZoom = 4000.f;
	int32 MinZoom = 500.f;

	FVector TargetLocation; 
	FRotator TargetRotation;

	bool CanRotate;
	
	float RotateSpeed = 2.f;
	float RotatePitchMin = 10.f;
	float RotatePitchMax = 80.f;
	
	

private:

	

	int32 team;
	int32 owningPlayer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Checks if camera rotation is valid or not 
	void EnableRotation();
	void DisableRotation();
	
	// Rotates the camera in Sections 
	void Left_Camera_Rotation();
	void Right_Camera_Rotation();

	// Rotates the camera with the middle mouse button (Freelook)
	void RotateHorizontal(float AxisValue);
	void RotateVertical(float AxisValue);

	void Zoom(float AxisValue);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
