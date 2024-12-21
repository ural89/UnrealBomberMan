// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void Explode();

private:
	FTimerHandle ExplosionTimerHandle;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABombProjectile> BombProjectileClass;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
