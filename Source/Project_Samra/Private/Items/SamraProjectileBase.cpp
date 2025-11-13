// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SamraProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "SamraFunctionLibrary.h"
#include "SamraGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/SamraHeroCharacter.h"

#include "SamraDebugHelper.h"

ASamraProjectileBase::ASamraProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);

	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComp= CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 100.f;
	ProjectileMovementComp->MaxSpeed = 100.f;
	ProjectileMovementComp->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;

}

void ASamraProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	}
	
}

void ASamraProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	/*APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!HitPawn || !USamraFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Debug::Print(TEXT("Player Hit"));

		return;
	}

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = USamraFunctionLibrary::NativeDoesActorHaveTag(HitPawn, SamraGameplayTags::Player_Status_Blocking);

	if (bIsPlayerBlocking)
	{
		bIsValidBlock = USamraFunctionLibrary::IsValidBlock(this, HitPawn);
	}

	FGameplayEventData Data;
	Data.Instigator = this;
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
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	Destroy();*/
}

void ASamraProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor))
	{
		return;
	}

	OverlappedActors.AddUnique(OtherActor);

	if (ASamraHeroCharacter* HitPawn = Cast<ASamraHeroCharacter>(OtherActor))
	{
		bool bIsValidBlock = false;

		const bool bIsPlayerBlocking = USamraFunctionLibrary::NativeDoesActorHaveTag(HitPawn, SamraGameplayTags::Player_Status_Blocking);

		if (bIsPlayerBlocking)
		{
			bIsValidBlock = USamraFunctionLibrary::IsValidBlock(this, HitPawn);
		}

		FGameplayEventData Data;
		Data.Instigator = this;
		Data.Target = HitPawn;

		if (bIsValidBlock)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				HitPawn,
				SamraGameplayTags::Player_Event_SuccessfulBlock,
				Data
			);
			Destroy();
		}
		else
		{
			HandleApplyProjectileDamage(HitPawn, Data);
		}
	}
}

void ASamraProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());

	const bool bWasApplied = USamraFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);

	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			InHitPawn,
			SamraGameplayTags::Player_Event_CriticalHitReact,
			InPayload
		);
	}
}


