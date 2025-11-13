// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SamraGameplayAbility.h"
#include "SamraHeroGameplayAbility.generated.h"

class ASamraHeroCharacter;
class ASamraHeroController;
class UHeroUIComponent;

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API USamraHeroGameplayAbility : public USamraGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	ASamraHeroCharacter* GetHeroCharcterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	ASamraHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	UHeroUIComponent* GetHeroUIComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Samra|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category = "Samra|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);

private:
	TWeakObjectPtr<ASamraHeroCharacter> CachedSamraHeroCharacter;
	TWeakObjectPtr<ASamraHeroController> CachedSamraHeroController;

};
