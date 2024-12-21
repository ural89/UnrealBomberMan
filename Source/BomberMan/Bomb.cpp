// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "BombProjectile.h"

ABomb::ABomb()
{
	PrimaryActorTick.bCanEverTick = true;
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb Mesh"));
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ABomb::Explode, 3.f);
}

void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABomb::Explode()
{
	FActorSpawnParameters SpawnParameters;
	for (size_t i = 0; i < 4; i++)
	{
		GetWorld()->SpawnActor<ABombProjectile>(
			BombProjectileClass,
			GetActorLocation(),
			GetActorRotation() + FRotator(0, i * 90, 0),
			SpawnParameters);
	}
}
