// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SamraGameplayTags.h"
#include "SamraFunctionLibrary.h"
#include "Characters/SamraEnenmyCharacter.h"
#include "Components/BoxComponent.h"

#include "SamraDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	//TODO: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = USamraFunctionLibrary::NativeDoesActorHaveTag(HitActor, SamraGameplayTags::Player_Status_Blocking);
	const bool bIsPlayerRolling = USamraFunctionLibrary::NativeDoesActorHaveTag(HitActor, SamraGameplayTags::Player_Status_Rolling);

	const bool bIsMyAttackUnblockable = USamraFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), SamraGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && bIsMyAttackUnblockable)
	{
		bIsValidBlock = USamraFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (/*bIsValidBlock ||*/ bIsPlayerRolling)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			SamraGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			SamraGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	ASamraEnenmyCharacter* OwningEnemyCharacter = GetOwningPawn<ASamraEnenmyCharacter>();

	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();
	UBoxComponent* TailCollisionBox = OwningEnemyCharacter->GetTailCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox && TailCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	case EToggleDamageType::Tail:
		TailCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
