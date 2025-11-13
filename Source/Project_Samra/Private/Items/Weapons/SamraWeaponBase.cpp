// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/SamraWeaponBase.h"
#include "Components/BoxComponent.h"
#include "SamraFunctionLibrary.h"
#include "Destructible/DestructibleActorBase.h"
#include "Interfaces/PawnCombatInterface.h"

#include "SamraDebugHelper.h"

ASamraWeaponBase::ASamraWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(10.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

UPawnCombatComponent* ASamraWeaponBase::GetPawnCombatComponent() const
{
	return nullptr;
}

void ASamraWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon : %s "), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (USamraFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);

		}
	}
	
	else if (ADestructibleActorBase* HitDestructible = Cast<ADestructibleActorBase>(OtherActor))
	{

		IPawnCombatInterface* CombatInterface = Cast<IPawnCombatInterface>(SweepResult.GetActor());

		if (CombatInterface)
		{
			CombatInterface->Execute_GetHit(SweepResult.GetActor(), SweepResult.ImpactPoint);
		}
	}
}

void ASamraWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon : %s "), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (USamraFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);

		}
	}
}

