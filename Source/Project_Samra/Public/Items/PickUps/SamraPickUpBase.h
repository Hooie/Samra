// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SamraPickUpBase.generated.h"

class USphereComponent;

UCLASS()
class PROJECT_SAMRA_API ASamraPickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASamraPickUpBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pick UP Interaction")
	USphereComponent* PickUpCollisionSphere;

	UFUNCTION()
	virtual void OnPickUpcollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};