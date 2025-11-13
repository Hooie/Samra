// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/SamraBaseGameMode.h"
#include "SamraSurvivalGameMode.generated.h"

UENUM(BlueprintType)
enum class ESamraSurvivalGameModeState : uint8
{
	InGame,
	PlayerDied
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChanged, ESamraSurvivalGameModeState, CurrentState);

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API ASamraSurvivalGameMode : public ASamraBaseGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentGameModeState(ESamraSurvivalGameModeState InState);

	UPROPERTY()
	ESamraSurvivalGameModeState CurrentGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChanged OnGameModeStateChanged;
};
