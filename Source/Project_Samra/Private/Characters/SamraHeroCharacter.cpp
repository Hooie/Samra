// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SamraHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/SamraInputComponent.h"
#include "SamraGameplayTags.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "AbilitySystem/SamraAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "SamraFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "SamraDebugHelper.h"

ASamraHeroCharacter::ASamraHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera Rotation

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

UPawnCombatComponent* ASamraHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* ASamraHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* ASamraHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void ASamraHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(SamraAbilitySystemComponent);
		}
	}
}

void ASamraHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	USamraInputComponent* SamraInputComponent = CastChecked<USamraInputComponent>(PlayerInputComponent);

	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_Sprint, ETriggerEvent::Started, this, &ThisClass::Input_SprintStart);
	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_Sprint, ETriggerEvent::Completed, this, &ThisClass::Input_SprintEnd);
	
	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwichTargetWheelTriggered);
	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwichTargetWheelCompleted);

	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_ControllerSwitchTarget_Left, ETriggerEvent::Triggered, this, &ThisClass::Input_SwichTargetControllerLBTriggered);
	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_ControllerSwitchTarget_Left, ETriggerEvent::Completed, this, &ThisClass::Input_SwichTargetControllerLBCompleted);

	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_ControllerSwitchTarget_Right, ETriggerEvent::Triggered, this, &ThisClass::Input_SwichTargetControllerRBTriggered);
	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_ControllerSwitchTarget_Right, ETriggerEvent::Completed, this, &ThisClass::Input_SwichTargetControllerRBCompleted);

	SamraInputComponent->BindNativeInputAction(InputConfigDataAsset, SamraGameplayTags::InputTag_PickUp_Potions, ETriggerEvent::Started, this, &ThisClass::Input_PickUpPotionsStarted);

	SamraInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);

}

void ASamraHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASamraHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASamraHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput((LookAxisVector.X) * MouseSensitivity);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput((LookAxisVector.Y * MouseSensitivity));
	}
}

void ASamraHeroCharacter::Input_SwichTargetWheelTriggered(const FInputActionValue& InputActionValue)
{
	WheelSwitchDirection = InputActionValue.Get<float>();
}

void ASamraHeroCharacter::Input_SwichTargetWheelCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		WheelSwitchDirection > 0.f ? SamraGameplayTags::Player_Event_SwitchTarget_Right : SamraGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void ASamraHeroCharacter::Input_SwichTargetControllerLBTriggered(const FInputActionValue& InputActionValue)
{
	bControllerSwitchLeft = true;
}

void ASamraHeroCharacter::Input_SwichTargetControllerRBTriggered(const FInputActionValue& InputActionValue)
{
	bControllerSwitchRight = true;
}

void ASamraHeroCharacter::Input_SwichTargetControllerLBCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SamraGameplayTags::Player_Event_SwitchTarget_Left,
		Data
		);
	bControllerSwitchLeft = false;
}


void ASamraHeroCharacter::Input_SwichTargetControllerRBCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SamraGameplayTags::Player_Event_SwitchTarget_Right,
		Data
		);
	bControllerSwitchRight = false;
}

void ASamraHeroCharacter::Input_SprintStart(const FInputActionValue& InputActionValue)
{
	if (USamraFunctionLibrary::NativeDoesActorHaveTag(this, SamraGameplayTags::Player_Status_TargetLock))
	{
		GetCharacterMovement()->MaxWalkSpeed = 350.f;
	}
	else 
	{
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}
}

void ASamraHeroCharacter::Input_SprintEnd(const FInputActionValue& InputActionValue)
{
	if (USamraFunctionLibrary::NativeDoesActorHaveTag(this, SamraGameplayTags::Player_Status_TargetLock))
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}
}

void ASamraHeroCharacter::Input_PickUpPotionsStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SamraGameplayTags::Player_Event_ConsumePotions,
		Data
	);
}

void ASamraHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	SamraAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void ASamraHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	SamraAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
