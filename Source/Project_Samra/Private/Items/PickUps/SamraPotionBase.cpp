// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/SamraPotionBase.h"
#include "Characters/SamraHeroCharacter.h"
#include "AbilitySystem/SamraAbilitySystemComponent.h"
#include "SamraGameplayTags.h"

void ASamraPotionBase::Consume(USamraAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(PotionGameplayEffectClass);

	UGameplayEffect* EffectCDO =  PotionGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnPotionConsumed();

}

void ASamraPotionBase::OnPickUpcollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASamraHeroCharacter* OverlappedHeroCharacter = Cast<ASamraHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetSamraAbilitySystemComponent()->TryActivateAbilityByTag(SamraGameplayTags::Player_Ability_PickUp_Potions);
	}
}
