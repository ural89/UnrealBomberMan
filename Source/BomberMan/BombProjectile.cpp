// Fill out your copyright notice in the Description page of Project Settings.

#include "BombProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "BomberMan.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
ABombProjectile::ABombProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));

	bReplicates = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECC_BombProjectile);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
}

void ABombProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &ABombProjectile::OnHit);
	}
}
void ABombProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) // this is authority only call
{
	ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		if (AController *OwnerController = OwnerCharacter->Controller)
		{
			UGameplayStatics::ApplyDamage(
				OtherActor,
				Damage,
				OwnerController,
				this,
				UDamageType::StaticClass());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OwnerController is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerCharacter is null"));
	}
	Destroy(); // since destroy is already replicated fx can be called locally on destroy
}

void ABombProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABombProjectile::Destroyed()
{
	Super::Destroyed();
}
