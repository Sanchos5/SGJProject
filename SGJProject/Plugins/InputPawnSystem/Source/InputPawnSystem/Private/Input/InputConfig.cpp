// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"

UInputConfig::UInputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FTaggedInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	return nullptr;
}