// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SamraTypes/SamraStructTypes.h"

#include "SamraAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API USamraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "Samra|Ability", meta = (ApplyLevel="1"))
	void GrantHeroWeaponAbilities(const TArray<FSamraHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FSamraHeroSkillAbilitySet>& InSkillAbilities,int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Samra|Ability")
	void RemovedGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Samra|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);

};
