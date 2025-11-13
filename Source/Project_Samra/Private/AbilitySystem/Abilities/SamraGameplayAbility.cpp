// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/SamraGameplayAbility.h"
#include "AbilitySystem/SamraAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SamraFunctionLibrary.h"
#include "SamraGameplayTags.h"
#include "Characters/SamraHeroCharacter.h"
#include "Characters/SamraEnenmyCharacter.h"
#include "SamraDebugHelper.h"
#include "SamraFunctionLibrary.h"

void USamraGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == ESamraAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void USamraGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == ESamraAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* USamraGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

USamraAbilitySystemComponent* USamraGameplayAbility::GetSamraAbilitySystemComponentFromActorInfo() const
{
	return Cast<USamraAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle USamraGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetSamraAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle USamraGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ESamraSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? ESamraSuccessType::Successful : ESamraSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

void USamraGameplayAbility::EnemyApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResults)
{
	if (InHitResults.IsEmpty())
	{
		return;
	}

	APawn* OwningPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());


	for (const FHitResult& Hit : InHitResults)
	{
		if (ASamraHeroCharacter * HitPawn = Cast<ASamraHeroCharacter>(Hit.GetActor()))
		{
			if (USamraFunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
			{
				bool bIsValidBlock = false;

				const bool bIsPlayerBlocking = USamraFunctionLibrary::NativeDoesActorHaveTag(HitPawn, SamraGameplayTags::Player_Status_Blocking);

				if (bIsPlayerBlocking)
				{
					bIsValidBlock = USamraFunctionLibrary::IsValidBlock(GetOwningActorFromActorInfo(), HitPawn);
				}

				FGameplayEventData Data;
				Data.Instigator = OwningPawn;
				Data.Target = HitPawn;

				if (bIsValidBlock)
				{
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						HitPawn,
						SamraGameplayTags::Player_Event_SuccessfulBlock,
						Data
					);
				}
				else
				{
					FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(HitPawn, InSpecHandle);

					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						HitPawn,
						SamraGameplayTags::Player_Event_CriticalHitReact,
						Data
					);
				}
			}

		}
	}
}

void USamraGameplayAbility::HeroApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResults)
{
	if (InHitResults.IsEmpty())
	{
		return;
	}

	APawn* OwningPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());

	for (const FHitResult& Hit : InHitResults)
	{
		if (ASamraEnenmyCharacter* HitPawn = Cast<ASamraEnenmyCharacter>(Hit.GetActor()))
		{
			if (USamraFunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(HitPawn, InSpecHandle);
				
				if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
				{
					if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
					{
						FGameplayEventData Data;
						Data.Instigator = OwningPawn;
						Data.Target = HitPawn;

						UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
							HitPawn,
							SamraGameplayTags::Shared_Event_HitReact,
							Data
						);
					}
				}
			}

		}
	}
}
