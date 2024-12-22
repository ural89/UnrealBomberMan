// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableWall.h"

ADestructableWall::ADestructableWall()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionObjectType(ECC_WorldStatic);

}

void ADestructableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestructableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &ADestructableWall::ReceiveDamage);
	}

}

void ADestructableWall::ReceiveDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatorController, AActor *DamageCauser)
{
	Destroy();
}
