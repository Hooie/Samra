// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SamraGameplayAbility.h"
#include "SamraEnemyGameplayAbility.generated.h"

class ASamraEnenmyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API USamraEnemyGameplayAbility : public USamraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	ASamraEnenmyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr< ASamraEnenmyCharacter> CachedSamraEnemyCharacter;
};
