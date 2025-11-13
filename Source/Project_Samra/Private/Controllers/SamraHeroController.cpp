// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SamraHeroController.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/InputDeviceSubsystem.h"

ASamraHeroController::ASamraHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId ASamraHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}

bool ASamraHeroController::IsUsingGamepad() const
{
	UInputDeviceSubsystem* InputDeviceSubsystem = GetGameInstance()->GetEngine()->GetEngineSubsystem<UInputDeviceSubsystem>();
	if (InputDeviceSubsystem)
	{
		FHardwareDeviceIdentifier MostRecentDevice = InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(GetPlatformUserId());
		if (MostRecentDevice.PrimaryDeviceType == EHardwareDevicePrimaryType::Gamepad)
		{
			return true;
		}
	}

	return false;
}