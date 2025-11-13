// Fill out your copyright notice in the Description page of Project Settings.


#include "SamraFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SamraAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "SamraGameplayTags.h"
#include "SamraTypes/SamraCountDownAction.h"
#include "GameInstances/SamraGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SamraSaveGame.h"
#include "Physics/Experimental/PhysScene_Chaos.h"

#include "SamraDebugHelper.h"
USamraAbilitySystemComponent* USamraFunctionLibrary::NativeGetSamraASCFromActor(AActor* InActor)
{
    check(InActor);

    return CastChecked<USamraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void USamraFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    USamraAbilitySystemComponent* ASC = NativeGetSamraASCFromActor(InActor);

    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }
}

void USamraFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    USamraAbilitySystemComponent* ASC = NativeGetSamraASCFromActor(InActor);

    if (ASC->HasMatchingGameplayTag(TagToRemove))
    {
        ASC->RemoveLooseGameplayTag(TagToRemove);
    }
}

bool USamraFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    USamraAbilitySystemComponent* ASC = NativeGetSamraASCFromActor(InActor);

    return ASC->HasMatchingGameplayTag(TagToCheck);
}

void USamraFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESamraConfirmType& OutConfirmType)
{
    OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ESamraConfirmType::Yes : ESamraConfirmType::No;
}

UPawnCombatComponent* USamraFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

    if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return PawnCombatInterface->GetPawnCombatComponent();
    }
	return nullptr;
}

UPawnCombatComponent* USamraFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, ESamraValidType& OutValidType)
{
    UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? ESamraValidType::Valid : ESamraValidType::Invalid; 

    return CombatComponent;
}

bool USamraFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

    IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
    IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

    if (QueryTeamAgent && TargetTeamAgent)
    {
        return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
    }

    return false;
}

FGameplayTag USamraFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
    check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
    const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

    const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
    OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

    const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

    if (CrossResult.Z < 0.f)
    {
        OutAngleDifference *= -1.f;
    }

    if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
    {
        return SamraGameplayTags::Shared_Status_HitReact_Front;
    }
    else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
    {
        return SamraGameplayTags::Shared_Status_HitReact_Left;
    }
    else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
    {
        return SamraGameplayTags::Shared_Status_HitReact_Back;
    }
    else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
    {
        return SamraGameplayTags::Shared_Status_HitReact_Right;
    }

    return SamraGameplayTags::Shared_Status_HitReact_Front;
}

bool USamraFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
    check(InAttacker && InDefender);

    // Defender 전방(수평)과 Defender→Attacker(수평)
    FVector F = InDefender->GetActorForwardVector();
    F.Z = 0.f;
    const double Fx = F.X, Fy = F.Y;
    const double FLen2 = Fx * Fx + Fy * Fy;
    if (FLen2 <= KINDA_SMALL_NUMBER) return false;

    const FVector A = InAttacker->GetActorLocation();
    const FVector D = InDefender->GetActorLocation();

    const double Dx = (double)A.X - (double)D.X;
    const double Dy = (double)A.Y - (double)D.Y;
    const double DLen2 = Dx * Dx + Dy * Dy;
    if (DLen2 <= KINDA_SMALL_NUMBER) return true; // 거의 같은 위치면 허용(원하면 false)

    const double Dot = Fx * Dx + Fy * Dy;

    // 1) 앞반구(전방) 조건: Dot > 0 이어야 함 (뒤쪽이면 바로 false)
    if (Dot <= 0.0) return false;

    // 2) 시야각 60도 조건: dot^2 >= cos^2(60°)*|F|^2*|D|^2,  cos^2(60°)=0.25
    return (Dot * Dot) >= (0.25 * FLen2 * DLen2);

 //   check(InAttacker && InDefender);

 //   const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	////const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < -0.1f ? TEXT("Valid Block") : TEXT("Invalid Block"));

 ////   Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);

 //   return DotResult < -0.1f;
}

void USamraFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, ESamraCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") ESamraCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
    UWorld* World = nullptr;

    if (GEngine)
    {
        World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    }

    if (!World)
    {
        return;
    }

    FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

    FSamraCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FSamraCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

    if (CountDownInput == ESamraCountDownActionInput::Start)
    {
        if (!FoundAction)
        {
            LatentActionManager.AddNewAction(
                LatentInfo.CallbackTarget,
                LatentInfo.UUID,
                new FSamraCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
                );
        }
    }
    
    if(CountDownInput == ESamraCountDownActionInput::Cancel)
    {
        if (FoundAction)
        {
            FoundAction->CancelAction();
        }
	}

}

bool USamraFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    USamraAbilitySystemComponent* SourceASC = NativeGetSamraASCFromActor(InInstigator);
    USamraAbilitySystemComponent* TargetASC = NativeGetSamraASCFromActor(InTargetActor);

    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

    return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

USamraGameInstance* USamraFunctionLibrary::GetsamraGameInstance(const UObject* WorldContextObject)
{
    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            return World->GetGameInstance<USamraGameInstance>();
        }
    }
    
    return nullptr;
}

void USamraFunctionLibrary::ToggleInputMode(ESamraInputMode InInputMode, const UObject* WorldContextObject)
{
    APlayerController* PlayerController = nullptr;

    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            PlayerController = World->GetFirstPlayerController();
        }
    }

    if (!PlayerController)
    {
        return;
    }

    FInputModeGameOnly GameOnlyMode;
    FInputModeUIOnly UIOnlyMode;
    FInputModeGameAndUI GameAndUIMode;

    switch(InInputMode)
    { 
    case ESamraInputMode :: GameOnly:

        PlayerController->SetInputMode(GameOnlyMode);
        PlayerController->bShowMouseCursor = false;

        break;

    case ESamraInputMode::UIOnly:

        PlayerController->SetInputMode(UIOnlyMode);
        PlayerController->bShowMouseCursor = true;

        break;

    case ESamraInputMode::GameAndUIOnly:

        PlayerController->SetInputMode(GameAndUIMode);
        PlayerController->bShowMouseCursor = true;

        break;
        
    } 
}

void USamraFunctionLibrary::SaveCurrentGameState(FGameplayTag InSaveSlot, float InPlayerHP, float InPlayerStamina, FVector InPlayerLocation)
{
    USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(USamraSaveGame::StaticClass());

    if (USamraSaveGame* SamraSaveGameObject = Cast<USamraSaveGame>(SaveGameObject))
    {
        SamraSaveGameObject->SavedHP = InPlayerHP;
        SamraSaveGameObject->SavedStamina = InPlayerStamina;
        SamraSaveGameObject->SavedPlayerLocation = InPlayerLocation;

        const bool bWasSaved = UGameplayStatics::SaveGameToSlot(SamraSaveGameObject, InSaveSlot.ToString(), 0);

        Debug::Print(bWasSaved ? TEXT("Successfully saved") : TEXT("Save Failed"));
    }
}

bool USamraFunctionLibrary::TryLoadSavedGameState(FGameplayTag OutSaveSlot, float& OutPlayerHP, float& OutPlayerStamina, FVector& OutPlayerLocation)
{
    if (UGameplayStatics::DoesSaveGameExist(OutSaveSlot.ToString(), 0))
    {
        USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(OutSaveSlot.ToString(), 0);

        if (USamraSaveGame* SamraSaveGameObject = Cast<USamraSaveGame>(SaveGameObject))
        {
            OutPlayerHP = SamraSaveGameObject->SavedHP;
            OutPlayerStamina = SamraSaveGameObject->SavedStamina;
            OutPlayerLocation = SamraSaveGameObject->SavedPlayerLocation;
            
            return true;
        }
    }

    return false;
}

void USamraFunctionLibrary::UnregisterAsyncPhysicsActor(AActor* actor)
{
    if (FPhysScene_Chaos* Scene = static_cast<FPhysScene_Chaos*>(actor->GetWorld()->GetPhysicsScene()))
    {
        Scene->UnregisterAsyncPhysicsTickActor(actor);
        Debug::Print(TEXT("Unload"));
    }
}

void USamraFunctionLibrary::RegisterAsyncPhysicsActor(AActor* actor)
{
    if (FPhysScene_Chaos* Scene = static_cast<FPhysScene_Chaos*>(actor->GetWorld()->GetPhysicsScene()))
    {
        Scene->RegisterAsyncPhysicsTickActor(actor);
    }
}
