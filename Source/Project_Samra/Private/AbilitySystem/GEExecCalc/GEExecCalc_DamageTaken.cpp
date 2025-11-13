// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/SamraAttributeSet.h"
#include "SamraGameplayTags.h"

#include "SamraDebugHelper.h"

struct FSamraDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FSamraDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USamraAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USamraAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USamraAttributeSet, DamageTaken, Target, false);
	}
};

static const FSamraDamageCapture& GetSamraDamageCapture()
{
	static FSamraDamageCapture SamraDamageCapture;
	return SamraDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/*Slow way of doing capture*/
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	USamraAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(USamraAttributeSet, AttackPower)
	//);

	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);

	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	RelevantAttributesToCapture.Add(GetSamraDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetSamraDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetSamraDamageCapture().DamageTakenDef);

}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSamraDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	//Debug::Print(TEXT("Source Attack Power"), SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedAttackComboCount = 0;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(SamraGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"), BaseDamage);

		}

		if (TagMagnitude.Key.MatchesTagExact(SamraGameplayTags::Player_SetByCaller_AttackType_Normal))
		{
			UsedAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedAttackComboCount"), UsedAttackComboCount);

		}


	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSamraDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	//Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	//Attack Damage Calculation 
	if (UsedAttackComboCount != 0)
	{
		const float DamageIncreasePercentAttack = (UsedAttackComboCount - 1) * 0.05f + 1.f;

		BaseDamage *= DamageIncreasePercentAttack;
		//Debug::Print(TEXT("ScaledBaseDamageAttack"), BaseDamage);

	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	//Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetSamraDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
