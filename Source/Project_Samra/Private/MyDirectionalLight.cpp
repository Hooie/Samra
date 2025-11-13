// MyDirectionalLight.cpp
#include "MyDirectionalLight.h"
#include "Components/BoxComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "GameFramework/Character.h"

AMyDirectionalLight::AMyDirectionalLight()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    DirectionalLightComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLight"));
    DirectionalLightComponent->SetupAttachment(RootComponent);
    DirectionalLightComponent->Intensity = 3.0f;
    DirectionalLightComponent->bUseTemperature = true;
	DirectionalLightComponent->Temperature = 6500.0f;
    DirectionalLightComponent->LightSourceAngle = 0.5357f;
    DirectionalLightComponent->SetRelativeRotation(FRotator(0.f, -30.f, 0.f));

    // 트리거 볼륨 1
    MorningTriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume1"));
    MorningTriggerVolume->SetupAttachment(RootComponent);
    MorningTriggerVolume->SetRelativeLocation(FVector(300.f, 0.f, 0.f));
    MorningTriggerVolume->SetBoxExtent(FVector(100.f));
    MorningTriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    MorningTriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // 트리거 볼륨 2
    AfternoonTriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume2"));
    AfternoonTriggerVolume->SetupAttachment(RootComponent);
    AfternoonTriggerVolume->SetRelativeLocation(FVector(0.f, 300.f, 0.f));
    AfternoonTriggerVolume->SetBoxExtent(FVector(100.f));
    AfternoonTriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    AfternoonTriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


    // 트리거 볼륨 3
    NightTriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume3"));
    NightTriggerVolume->SetupAttachment(RootComponent);
    NightTriggerVolume->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
    NightTriggerVolume->SetBoxExtent(FVector(100.f));
    NightTriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    NightTriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


    // 각 회전값 초기값 설정 (에디터에서 변경 가능)

}

void AMyDirectionalLight::BeginPlay()
{
    MorningTriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMyDirectionalLight::OnTrigger1Overlap);
    AfternoonTriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMyDirectionalLight::OnTrigger2Overlap);
    NightTriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMyDirectionalLight::OnTrigger3Overlap);
}

void AMyDirectionalLight::OnTrigger1Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA<ACharacter>())
    {
        DirectionalLightComponent->SetWorldRotation(MorningTime);
        DirectionalLightComponent->Temperature = MorningLightTemperature;
    }
}

void AMyDirectionalLight::OnTrigger2Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA<ACharacter>())
    {
        DirectionalLightComponent->SetWorldRotation(AfternoonTime);
		DirectionalLightComponent->Temperature = AfternoonLightTemperature;
    }
}

void AMyDirectionalLight::OnTrigger3Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA<ACharacter>())
    {
        DirectionalLightComponent->SetWorldRotation(NightTime);
		DirectionalLightComponent->Temperature = NightLightTemperature;
    }
}