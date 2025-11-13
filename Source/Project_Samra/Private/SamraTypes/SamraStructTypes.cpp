// Fill out your copyright notice in the Description page of Project Settings.


#include "SamraTypes/SamraStructTypes.h"
#include "AbilitySystem/Abilities/SamraHeroGameplayAbility.h"

bool FSamraHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
