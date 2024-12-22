// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCreator.h"

// Sets default values
AMapCreator::AMapCreator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMapCreator::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		CreateMap();
	}
}

// Called every frame
void AMapCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMapCreator::CreateMap()
{
	FActorSpawnParameters SpawnParameters;
	for (size_t i = 0; i < GridSizeX; i++)
	{
		for (size_t j = 0; j < GridSizeY; j++)
		{
			GetWorld()->SpawnActor<AActor>(
				WallClass,
				FVector(GetActorLocation().X + WallDistance * i, GetActorLocation().Y + WallDistance * j, 1),
				FRotator::ZeroRotator,
				SpawnParameters);
		}
	}
}
