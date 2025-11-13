// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_PickUpItems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/SamraHeroCharacter.h"
#include "Items/PickUps/SamraPotionBase.h"
#include "Components/UI/HeroUIComponent.h"

void UHeroGameplayAbility_PickUpItems::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetHeroUIComponentFromActorInfo()->OnPotionInteracted.Broadcast(true);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_PickUpItems::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetHeroUIComponentFromActorInfo()->OnPotionInteracted.Broadcast(false);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_PickUpItems::CollectPotions()
{
	CollectedPotions.Empty();

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharcterFromActorInfo(),
		GetHeroCharcterFromActorInfo()->GetActorLocation(),
		GetHeroCharcterFromActorInfo()->GetActorLocation() + -GetHeroCharcterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		(-GetHeroCharcterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		PotionTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (ASamraPotionBase* FoundPotion = Cast<ASamraPotionBase>(TraceHit.GetActor()))
		{
			CollectedPotions.AddUnique(FoundPotion);
		}
	}
	
	if (CollectedPotions.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}

}

void UHeroGameplayAbility_PickUpItems::ConsumePotions()
{
	if (CollectedPotions.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (ASamraPotionBase* CollectedPotion : CollectedPotions)
	{
		if (CollectedPotion)
		{
			CollectedPotion->Consume(GetSamraAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
	}
}
