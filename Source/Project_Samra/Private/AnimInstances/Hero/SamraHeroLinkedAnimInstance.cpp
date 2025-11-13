// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/SamraHeroLinkedAnimInstance.h"
#include "AnimInstances/Hero/SamraHeroAnimInstance.h"

USamraHeroAnimInstance* USamraHeroLinkedAnimInstance::GetHeroAnimInstance() const
{
    return Cast<USamraHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
