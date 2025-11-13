// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SamraEnemyGameplayAbility.h"
#include "Characters/SamraEnenmyCharacter.h"
#include "AbilitySystem/SamraAbilitySystemComponent.h"
#include "SamraGameplayTags.h"

ASamraEnenmyCharacter* USamraEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!CachedSamraEnemyCharacter.IsValid())
    {
        CachedSamraEnemyCharacter = Cast<ASamraEnenmyCharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedSamraEnemyCharacter.IsValid() ? CachedSamraEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* USamraEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle USamraEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
    check(EffectClass);

    FGameplayEffectContextHandle ContextHandle = GetSamraAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle EffectSpecHandle = GetSamraAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );

    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        SamraGameplayTags::Shared_SetByCaller_BaseDamage,
        InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
    );

    return EffectSpecHandle;
}
