// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"

#include "SamraHeroController.generated.h"


/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API ASamraHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ASamraHeroController();

	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface

	UFUNCTION(BlueprintCallable, Category = "InputDevice")
	bool IsUsingGamepad() const;

private:
	FGenericTeamId HeroTeamId;
};
