// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PawnCombatInterface.h"

#include "DestructibleActorBase.generated.h"

class UGeometryCollecitonComponent;

UCLASS()
class PROJECT_SAMRA_API ADestructibleActorBase : public AActor, public IPawnCombatInterface
{
	GENERATED_BODY()
	
	//~ Begin PawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface Interface

public:	
	// Sets default values for this actor's properties
	ADestructibleActorBase();

private:

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HitCount = 0;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

};
