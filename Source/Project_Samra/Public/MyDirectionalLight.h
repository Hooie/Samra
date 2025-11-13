// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "GameFramework/Actor.h"

#include "MyDirectionalLight.generated.h"

/**
 * 
 */

class UBoxComponent;

UCLASS()
class PROJECT_SAMRA_API AMyDirectionalLight : public AActor
{
    GENERATED_BODY()

public:
    AMyDirectionalLight();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UDirectionalLightComponent* DirectionalLightComponent;

    // 트리거 볼륨 3개
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* MorningTriggerVolume;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* AfternoonTriggerVolume;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* NightTriggerVolume;

    // 아침에 해당하는 시간
    UPROPERTY(EditAnywhere, Category = "Level_Time")
    FRotator MorningTime;

    UPROPERTY(EditAnywhere, Category = "Level_Time")
    FRotator AfternoonTime;

    UPROPERTY(EditAnywhere, Category = "Level_Time")
    FRotator NightTime;

    UPROPERTY(EditAnywhere, Category = "Level_Time")
    float MorningLightTemperature;

    UPROPERTY(EditAnywhere, Category = "Level_Time")
    float AfternoonLightTemperature;

    UPROPERTY(EditAnywhere, Category = "Level_Time")
    float NightLightTemperature;

    // 오버랩 핸들러
    UFUNCTION()
    void OnTrigger1Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


    UFUNCTION()
    void OnTrigger2Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


    UFUNCTION()
    void OnTrigger3Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};