// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/SamraSurvivalGameMode.h"

void ASamraSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASamraSurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASamraSurvivalGameMode::SetCurrentGameModeState(ESamraSurvivalGameModeState InState)
{
	CurrentGameModeState = InState;

	OnGameModeStateChanged.Broadcast(CurrentGameModeState);
}
