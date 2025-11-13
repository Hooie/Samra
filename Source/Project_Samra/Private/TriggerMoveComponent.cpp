#include "TriggerMoveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

UTriggerMoveComponent::UTriggerMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		ForwardAnchor = Owner->GetActorLocation();
		BackwardAnchor = ForwardAnchor + RelativeTargetOffset;
		bIsMoving = false;
		bMovingForward = true;
		bCanTrigger = true;
	}
}

void UTriggerMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsMoving)
	{
		HandleTriggerCheck();  // 이동 중이 아닐 때만 트리거 체크
	}
	else
	{
		HandleMovement(DeltaTime); // 이동 중이면 이동 처리
	}
}

void UTriggerMoveComponent::HandleTriggerCheck()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return;

	FVector TriggerAnchor = bMovingForward ? ForwardAnchor : BackwardAnchor;
	FVector TriggerLocation = TriggerAnchor + RelativeTriggerOffset;

	float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), TriggerLocation);

	if (bCanTrigger && Distance <= TriggerRadius)
	{
		bCanTrigger = false;
		bDidShake = false;

		// 카메라 흔들기
		if (CameraShakeClass)
		{
			if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				PC->ClientStartCameraShake(CameraShakeClass);
				bDidShake = true;
			}
		}

		// 1초 뒤에 이동 시작
		GetWorld()->GetTimerManager().SetTimer(
			MoveDelayTimerHandle, this, &UTriggerMoveComponent::StartMovement, 1.0f, false
		);
	}
}

void UTriggerMoveComponent::StartMovement()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	StartLocation = Owner->GetActorLocation();
	bMovingForward = !bMovingForward;
	TargetLocation = bMovingForward ? ForwardAnchor + RelativeTargetOffset : BackwardAnchor;
	LastDisplacement = TargetLocation - StartLocation;

	bIsMoving = true;
}

void UTriggerMoveComponent::HandleMovement(float DeltaTime)
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	FVector CurrentLocation = Owner->GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector DeltaMove = Direction * MoveSpeed * DeltaTime;
	FVector NewLocation = CurrentLocation + DeltaMove;

	if (FVector::Dist(NewLocation, StartLocation) >= FVector::Dist(TargetLocation, StartLocation))
	{
		NewLocation = TargetLocation;
		bIsMoving = false;
		bDidShake = false;

		if (bMovingForward)
		{
			ForwardAnchor = StartLocation;
			BackwardAnchor = TargetLocation;
		}
		else
		{
			ForwardAnchor = TargetLocation;
			BackwardAnchor = StartLocation;
		}

		bMovingForward = !bMovingForward;

		GetWorld()->GetTimerManager().SetTimer(
			ReturnTimerHandle, this, &UTriggerMoveComponent::EnableTrigger, ReturnDelay, false
		);
	}

	Owner->SetActorLocation(NewLocation);
}

void UTriggerMoveComponent::EnableTrigger()
{
	bCanTrigger = true;
}
