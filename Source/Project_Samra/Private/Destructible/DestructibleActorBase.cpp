// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructible/DestructibleActorBase.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

UPawnCombatComponent* ADestructibleActorBase::GetPawnCombatComponent() const
{
	return nullptr;
}

// Sets default values
ADestructibleActorBase::ADestructibleActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GeometryCollection->SetGenerateOverlapEvents(true);
}

void ADestructibleActorBase::GetHit_Implementation(const FVector& ImpactPoint)
{
}

