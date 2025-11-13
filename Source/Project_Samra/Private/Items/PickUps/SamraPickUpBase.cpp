// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/SamraPickUpBase.h"
#include "Components/SphereComponent.h"

ASamraPickUpBase::ASamraPickUpBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickUpcollisionSphereBeginOverlap);

}

void ASamraPickUpBase::OnPickUpcollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
