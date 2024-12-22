// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructableWall.generated.h"

UCLASS()
class BOMBERMAN_API ADestructableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestructableWall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void ReceiveDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatorController, AActor *DamageCauser);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
