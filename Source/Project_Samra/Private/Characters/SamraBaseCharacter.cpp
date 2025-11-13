// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SamraBaseCharacter.h"
#include "AbilitySystem/SamraAbilitySystemComponent.h"
#include "AbilitySystem/SamraAttributeSet.h"
#include "MotionWarpingComponent.h"


// Sets default values
ASamraBaseCharacter::ASamraBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false; //ignore VFX decal
	
	SamraAbilitySystemComponent = CreateDefaultSubobject<USamraAbilitySystemComponent>(TEXT("SamraAbilitySystemComponent"));
	SamraAttributeSet = CreateDefaultSubobject<USamraAttributeSet>(TEXT("SamraAttributeSet"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

}

UAbilitySystemComponent* ASamraBaseCharacter::GetAbilitySystemComponent() const
{
	return GetSamraAbilitySystemComponent();
}

UPawnCombatComponent* ASamraBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* ASamraBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void ASamraBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (SamraAbilitySystemComponent)
	{
		SamraAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
