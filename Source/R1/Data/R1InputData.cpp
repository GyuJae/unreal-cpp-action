// Fill out your copyright notice in the Description page of Project Settings.
#include "R1InputData.h"

const UInputAction* UR1InputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FR1InputAction& InputAction : InputActions)
	{
		if (InputAction.InputTag.MatchesTag(InputTag))
		{
			return InputAction.InputAction.Get();
		}
	}

	//UE_LOG(LogR1, Error, TEXT("Input action with tag %s not found"), *InputTag.ToString());

	return nullptr;
}
