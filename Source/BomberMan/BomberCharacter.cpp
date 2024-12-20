// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABomberCharacter::ABomberCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABomberCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); 
	bUseControllerRotationYaw = false;
}

void ABomberCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABomberCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABomberCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABomberCharacter::MoveRight);
}

void ABomberCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(FVector::ForwardVector, AxisValue);
}

void ABomberCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(FVector::RightVector, AxisValue);
}
