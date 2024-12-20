// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberAnimInstance.h"
#include "BomberCharacter.h"

void UBomberAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    BomberCharacter = Cast<ABomberCharacter>(TryGetPawnOwner());
}

void UBomberAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);
    if (BomberCharacter != nullptr)
    {
        FVector Velocity = BomberCharacter->GetVelocity();
        Velocity.Z = 0;
        Speed = Velocity.Size();
    }
    else
    {
        BomberCharacter = Cast<ABomberCharacter>(TryGetPawnOwner());
    }
}
