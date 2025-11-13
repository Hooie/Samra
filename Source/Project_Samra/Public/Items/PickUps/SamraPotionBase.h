// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/SamraPickUpBase.h"
#include "SamraPotionBase.generated.h"

class USamraAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API ASamraPotionBase : public ASamraPickUpBase
{
	GENERATED_BODY()
	
public:
	void Consume(USamraAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:
	virtual void OnPickUpcollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Potion Consumed"))
	void BP_OnPotionConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> PotionGameplayEffectClass;
};
