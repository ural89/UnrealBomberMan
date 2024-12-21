// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"

// Sets default values
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
	UE_LOG(LogTemp, Warning, TEXT("EXPLODED!!"));
}
