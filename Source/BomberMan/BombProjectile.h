// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombProjectile.generated.h"

UCLASS()
class BOMBERMAN_API ABombProjectile : public AActor
{
	GENERATED_BODY()

public:
	ABombProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

private:
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent *MovementComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent *CollisionBox;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
