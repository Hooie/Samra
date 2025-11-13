// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SamraTypes/SamraEnumTypes.h"
#include "SamraFunctionLibrary.generated.h"

class USamraAbilitySystemComponent;
class UPawnCombatComponent;
class USamraGameInstance;

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API USamraFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static USamraAbilitySystemComponent* NativeGetSamraASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESamraConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, ESamraValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Samra|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Samra|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Samra|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, 
	float& OutRemainingTime, ESamraCountDownActionInput CountDownInput, 
	UPARAM(DisplayName = "Output") ESamraCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintPure, Category = "Samra|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static USamraGameInstance* GetsamraGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(ESamraInputMode InInputMode, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary")
	static void SaveCurrentGameState(FGameplayTag InSaveSlot, float InPlayerHP, float InPlayerStamina, FVector InPlayerLocation);

	UFUNCTION(BlueprintCallable, Category = "Samra|FunctionLibrary")
	static bool TryLoadSavedGameState(FGameplayTag OutSaveSlot,float& OutPlayerHP, float& OutPlayerStamina, FVector& OutPlayerLocation);

	UFUNCTION(BlueprintCallable, Category = "AsyncPhysics", meta = (DisplayName = "UnregisterAsyncPhysicsActor"))
	static void UnregisterAsyncPhysicsActor(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "AsyncPhysics", meta = (DisplayName = "RegisterAsyncPhysicsActor"))
	static void RegisterAsyncPhysicsActor(AActor* actor);
};
