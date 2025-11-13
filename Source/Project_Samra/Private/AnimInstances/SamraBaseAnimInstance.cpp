// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/SamraBaseAnimInstance.h"
#include "SamraFunctionLibrary.h"

bool USamraBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return USamraFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
