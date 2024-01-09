// Fill out your copyright notice in the Description page of Project Settings.


#include "UserCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AUserCharacter::AUserCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	GetCharacterMovement()->MaxWalkSpeed = 2000;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 3000.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	CameraBoom->bEnableCameraLag = true;

	
	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void AUserCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUserCharacter::EnableRotation()
{
	CanRotate = true;
}

void AUserCharacter::DisableRotation()
{
	CanRotate = false;
}

void AUserCharacter::Left_Camera_Rotation()
{
	// CompRot combines 2 rotations, In this case A is the current rotation, B is the rotation we want to add. 
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0.f, 45.f, 0.f));
}

void AUserCharacter::Right_Camera_Rotation()
{
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0.f, -45.f, 0.f));
}

void AUserCharacter::RotateHorizontal(float AxisValue)
{
	// If the mouse hasnt moved return. 
	if(AxisValue == 0.f)
	{
		return;
	}
	// else if it has and the we can rotate then we compose A&B again, this time the Yaw rotation will be dynamic and dictated by the mouse movement. 
	if(CanRotate)
	{
		TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0.f, AxisValue, 0.f));
	}
}

void AUserCharacter::RotateVertical(float AxisValue)
{
		
	if(AxisValue == 0.f)
	{
		return;
	}
	
	// Checks Pitch rotation instead.
	if(CanRotate)
	{
		TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(AxisValue, 0.f, 0.f));
	}
}

void AUserCharacter::Zoom(float AxisValue)
{
	if(AxisValue == 0.f)
	{
		return;
	}

	const float Zoom = AxisValue * 100.f;
	TargetZoom = FMath::Clamp(Zoom + TargetZoom, MinZoom, MaxZoom);

}

// Called every frame
void AUserCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// zoom the camera in the desired direction
	const float InterpolatedZoom =  UKismetMathLibrary::FInterpTo(CameraBoom->TargetArmLength, TargetZoom, DeltaTime, ZoomSpeed);
	CameraBoom->TargetArmLength = InterpolatedZoom;

	// zoom the camera in the desired direction
	const FRotator InterpolatedRotation =  UKismetMathLibrary::RInterpTo(CameraBoom->GetRelativeRotation(), TargetRotation, DeltaTime, RotateSpeed);
	CameraBoom->SetRelativeRotation(InterpolatedRotation);
	
}

// Called to bind functionality to input
void AUserCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Zoom", this, &AUserCharacter::Zoom);
	
	// Freemove Camera
	InputComponent->BindAxis("RotateHorizontal", this, &AUserCharacter::RotateHorizontal);
	InputComponent->BindAxis("RotateVertical", this, &AUserCharacter::RotateVertical);
	
	// Camera Rotation
	InputComponent->BindAction("Rotate", IE_Pressed, this, &AUserCharacter::EnableRotation);
	InputComponent->BindAction("Rotate", IE_Released, this, &AUserCharacter::DisableRotation);
	InputComponent->BindAction("RotateLeft", IE_Pressed, this, &AUserCharacter::Left_Camera_Rotation);
	InputComponent->BindAction("RotateRight", IE_Pressed, this, &AUserCharacter::Right_Camera_Rotation);
}

