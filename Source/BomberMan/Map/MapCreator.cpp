#include "MapCreator.h"
#include "Engine/World.h"

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
			FVector SpawnLocation(
				GetActorLocation().X + WallDistance * i,
				GetActorLocation().Y + WallDistance * j,
				GetActorLocation().Z);

			GetWorld()->SpawnActor<AActor>(WallClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);

			if (i > 0 && j > 0 && i < GridSizeX - 1 && j < GridSizeY - 1)
			{
				float RandomValue = FMath::FRand();
				if (RandomValue <= DestructibleWallProbability)
				{
					FVector DestructibleWallLocation(
						GetActorLocation().X + WallDistance * i + WallDistance / 2.f,
						GetActorLocation().Y + WallDistance * j + WallDistance / 2.f,
						GetActorLocation().Z);

					GetWorld()->SpawnActor<AActor>(DestructableWallClass, DestructibleWallLocation, FRotator::ZeroRotator, SpawnParameters);
				}
				RandomValue = FMath::FRand();
				if (RandomValue <= DestructibleWallProbability)
				{
					FVector DestructibleWallLocation(
						GetActorLocation().X + WallDistance * i + WallDistance,
						GetActorLocation().Y + WallDistance * j + WallDistance / 2.f,
						GetActorLocation().Z);

					GetWorld()->SpawnActor<AActor>(DestructableWallClass, DestructibleWallLocation, FRotator::ZeroRotator, SpawnParameters);
				}
				RandomValue = FMath::FRand();
				if (RandomValue <= DestructibleWallProbability)
				{
					FVector DestructibleWallLocation(
						GetActorLocation().X + WallDistance * i + WallDistance / 2.f,
						GetActorLocation().Y + WallDistance * j + WallDistance,
						GetActorLocation().Z);

					GetWorld()->SpawnActor<AActor>(DestructableWallClass, DestructibleWallLocation, FRotator::ZeroRotator, SpawnParameters);
				}
			}
		}
	}
}
