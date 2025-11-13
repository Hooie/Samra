// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SamraHeroGameplayAbility.h"
#include "Characters/SamraHeroCharacter.h"
#include "Controllers/SamraHeroController.h"
#include "AbilitySystem/SamraAbilitySystemComponent.h"
#include "SamraGameplayTags.h"

ASamraHeroCharacter* USamraHeroGameplayAbility::GetHeroCharcterFromActorInfo()
{
    if (!CachedSamraHeroCharacter.IsValid())
    {
        CachedSamraHeroCharacter = Cast<ASamraHeroCharacter>(CurrentActorInfo->AvatarActor);
    }
    
    return CachedSamraHeroCharacter.IsValid() ? CachedSamraHeroCharacter.Get() : nullptr;
}

ASamraHeroController* USamraHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedSamraHeroController.IsValid())
    {
        CachedSamraHeroController = Cast<ASamraHeroController>(CurrentActorInfo->PlayerController);
    }

    return CachedSamraHeroController.IsValid() ? CachedSamraHeroController.Get() : nullptr;
}

UHeroCombatComponent* USamraHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharcterFromActorInfo()->GetHeroCombatComponent();
}

UHeroUIComponent* USamraHeroGameplayAbility::GetHeroUIComponentFromActorInfo()
{
    return GetHeroCharcterFromActorInfo()->GetHeroUIComponent();
}

FGameplayEffectSpecHandle USamraHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
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
        InWeaponBaseDamage
    );

    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
    }

    return EffectSpecHandle;
}

bool USamraHeroGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
    check(InCooldownTag.IsValid());

    FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

    TArray< TPair <float, float> > TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

    if (!TimeRemainingAndDuration.IsEmpty())
    {
        RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
        TotalCooldownTime = TimeRemainingAndDuration[0].Value;
    }

    return RemainingCooldownTime > 0.f;
}
