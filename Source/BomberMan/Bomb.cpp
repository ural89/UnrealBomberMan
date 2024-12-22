// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "BombProjectile.h"

ABomb::ABomb()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb Mesh"));
	BombMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BombMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SetRootComponent(BombMesh);
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ABomb::Explode, 3.f);
	BombMesh->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);
}

void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABomb::Explode()
{
	if (HasAuthority())
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = Cast<APawn>(GetOwner());
		SpawnParameters.Owner = Cast<APawn>(GetOwner());
		for (size_t i = 0; i < 4; i++)
		{
			GetWorld()->SpawnActor<ABombProjectile>(
				BombProjectileClass,
				GetActorLocation(),
				GetActorRotation() + FRotator(0, i * 90, 0),
				SpawnParameters);
		}
	Destroy();
	}
}

void ABomb::OnOverlapEnd(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	BombMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}
