// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/SamraWeaponBase.h"
#include "SamraTypes/SamraStructTypes.h"
#include "GameplayAbilitySpecHandle.h"

#include "SamraHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API ASamraHeroWeapon : public ASamraWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "WeaponData")
	FSamraHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

};
