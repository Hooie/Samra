// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SamraBaseAnimInstance.h"
#include "SamraHeroLinkedAnimInstance.generated.h"

class USamraHeroAnimInstance;

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API USamraHeroLinkedAnimInstance : public USamraBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Blueprintpure, meta = (BlueprintThreadSafe))
	USamraHeroAnimInstance* GetHeroAnimInstance() const;
};
