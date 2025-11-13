// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstances/SamraCharacterAnimInstance.h"
#include "Characters/SamraBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void USamraCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ASamraBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();

	}
}

void USamraCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().Size2D() > 0.f;
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	bIsFalling = OwningMovementComponent->IsFalling();
}
