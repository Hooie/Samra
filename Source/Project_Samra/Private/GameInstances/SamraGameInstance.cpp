// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstances/SamraGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"

//void USamraGameInstance::Init()
//{
//	Super::Init();
//
//	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
//	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorldLoaded);
//}
//
//void USamraGameInstance::OnPreLoadMap(const FString& PreLoadMap)
//{
//	const auto LoadingWidget = CreateWidget<UUserWidget>(this, LoadingWidgetClass.LoadSynchronous(), TEXT("LoadingScreen"));
//
//	TSharedRef<SWidget> LoadingSWidgetPtr = LoadingWidget->TakeWidget();
//
//	FLoadingScreenAttributes LoadingScreenAttributes;
//
//	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
//	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 5.f;
//	//LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
//	LoadingScreenAttributes.WidgetLoadingScreen = LoadingSWidgetPtr;
//
//	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
//}
//
//void USamraGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
//{
//	//GetMoviePlayer()->StopMovie();
//}
//
//TSoftObjectPtr<UWorld> USamraGameInstance::GetLevel(FString LevelName)
//{
//	if (MapList.IsEmpty()) {
//		UE_LOG(LogTemp, Warning, TEXT("Map List Is Null Please Fill"));
//		return nullptr;
//	}
//	return *MapList.Find(LevelName);
//}
//
//TSoftObjectPtr<UWorld> USamraGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
//{
//	for (const FSamraGameLevelSet& GameLevelSet : GameLevelSets)
//	{
//		if (!GameLevelSet.Isvalid()) continue;
//
//		if (GameLevelSet.LevelTag == InTag)
//		{
//			return GameLevelSet.Level;
//		}
//	}
//
//	return TSoftObjectPtr<UWorld>();
//}
