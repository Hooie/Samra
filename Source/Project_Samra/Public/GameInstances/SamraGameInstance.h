// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SamraGameplayTags.h"

#include "SamraGameInstance.generated.h"

//class UUserWidget;
//
//USTRUCT(BlueprintType)
//struct FSamraGameLevelSet
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditDefaultsOnly, meta = (Category = "GameData.Level"))
//	FGameplayTag LevelTag;
//
//	UPROPERTY(EditDefaultsOnly)
//	TSoftObjectPtr<UWorld> Level;
//	
//	bool Isvalid() const
//	{
//		return LevelTag.IsValid() && !Level.IsNull();
//	}
//	
//};

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API USamraGameInstance : public UGameInstance
{
	GENERATED_BODY()

//public:
//	TSoftObjectPtr<UWorld> GetLevel(FString LevelName);
//	
//	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Level"))
//	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;
//
//protected:
//	virtual void Init() override;
//
//	UFUNCTION()
//	void OnPreLoadMap(const FString& PreLoadMap);
//	
//	UFUNCTION()
//	void OnDestinationWorldLoaded(UWorld* LoadedWorld);
//
//	UPROPERTY(EditDefaultsOnly)
//	TSoftClassPtr<UUserWidget> LoadingWidgetClass;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
//	TArray<FSamraGameLevelSet> GameLevelSets;
//
//
//private:
//	UPROPERTY(EditDefaultsOnly, Category = "Level")
//	TMap<FString, TSoftObjectPtr<UWorld>> MapList;
};
