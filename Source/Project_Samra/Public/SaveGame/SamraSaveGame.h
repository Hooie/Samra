// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SamraTypes/SamraEnumTypes.h"

#include "SamraSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API USamraSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	float SavedHP;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	float SavedStamina;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector SavedPlayerLocation;

	//quest info

};
