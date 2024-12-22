// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapCreator.generated.h"

UCLASS()
class BOMBERMAN_API AMapCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapCreator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WallClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DestructableWallClass;

	void CreateMap();

	UPROPERTY(EditAnywhere)
	uint16 GridSizeX = 10;
	
	UPROPERTY(EditAnywhere)
	uint16 GridSizeY = 10;

	UPROPERTY(EditAnywhere)
	float WallDistance = 400;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DestructibleWallProbability = 0.3f;
};
