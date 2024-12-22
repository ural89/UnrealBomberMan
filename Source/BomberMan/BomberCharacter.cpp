// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Bomb.h"

ABomberCharacter::ABomberCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ABomberCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	bUseControllerRotationYaw = false;

	if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &ABomberCharacter::RecieveDamage);
	}
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
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ABomberCharacter::Fire);
}

void ABomberCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(FVector::ForwardVector, AxisValue);
}

void ABomberCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(FVector::RightVector, AxisValue);
}

void ABomberCharacter::Fire()
{
	ServerFire();
}
void ABomberCharacter::RecieveDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatorController, AActor *DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("DAMAGE TAKEN! %s"), *(DamagedActor->GetName()));
}
void ABomberCharacter::ServerFire_Implementation()
{
	FActorSpawnParameters SpawnParamameters;
	SpawnParamameters.Instigator = this;
	SpawnParamameters.Owner = this;
	GetWorld()->SpawnActor<ABomb>( //Bomb should be spawn from server
		BombClass, 
		GetActorLocation(),
		FRotator::ZeroRotator,
		SpawnParamameters);
}
