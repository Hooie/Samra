// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SamraBaseCharacter.h"
#include "GameplayTagContainer.h"

#include "SamraHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UHeroCombatComponent;
class UHeroUIComponent;

/**
 * 
 */
UCLASS()
class PROJECT_SAMRA_API ASamraHeroCharacter : public ASamraBaseCharacter
{
	GENERATED_BODY()
	
public:
	ASamraHeroCharacter();

	//~ Begin IPawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetHeroUIComponent() const override;

	//~ End IPawnUIInterface Interface

	UPROPERTY(EditAnywhere, Category = "input", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MouseSensitivity = 0.5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPhysicsHandleComponent* PhysicsHandle;

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	
	//jump cool time
	FTimerHandle CooldownTimerHandle;

private:

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;

#pragma endregion 

#pragma region Inputs
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;
	
	UPROPERTY()
	float WheelSwitchDirection = 0.f;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwichTargetWheelTriggered(const FInputActionValue& InputActionValue);
	void Input_SwichTargetWheelCompleted(const FInputActionValue& InputActionValue);

	//FVector2D SwitchDirection = FVector2D::ZeroVector;

	void Input_SwichTargetControllerLBTriggered(const FInputActionValue& InputActionValue);
	void Input_SwichTargetControllerRBTriggered(const FInputActionValue& InputActionValue);
	void Input_SwichTargetControllerLBCompleted(const FInputActionValue& InputActionValue);
	void Input_SwichTargetControllerRBCompleted(const FInputActionValue& InputActionValue);

	bool bControllerSwitchLeft = false;
	bool bControllerSwitchRight = false;

	void Input_SprintStart(const FInputActionValue& InputActionValue);
	void Input_SprintEnd(const FInputActionValue& InputActionValue);

	void Input_PickUpPotionsStarted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

#pragma endregion 

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }

};
