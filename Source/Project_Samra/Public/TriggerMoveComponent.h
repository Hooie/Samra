#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraShakeBase.h"
#include "TriggerMoveComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_SAMRA_API UTriggerMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTriggerMoveComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//트리거의 위치, 액터의 정중앙으로부터의 상대좌표.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	FVector RelativeTriggerOffset = FVector(0, 0, 40);

	//트리거와의 거리 허용 오차, 낮을 수록 정중앙에 가야함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	float TriggerRadius = 70.f;

	//이동할 거리 3차원 벡터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector RelativeTargetOffset = FVector(1000, 1000, 1000);

	//액터 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;
	//트리거 재작동 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ReturnDelay = 5.0f;

private:
	FVector StartLocation;
	FVector TargetLocation;
	FVector LastDisplacement;
	FVector ForwardAnchor;
	FVector BackwardAnchor;


	bool bIsMoving = false;
	bool bMovingForward = true;
	bool bCanTrigger = true;
	bool bDidShake = false;

	FTimerHandle ReturnTimerHandle;

	void EnableTrigger();

	UFUNCTION()
	void StartMovement();

	void HandleTriggerCheck();
	void HandleMovement(float DeltaTime);

	FTimerHandle MoveDelayTimerHandle;

};