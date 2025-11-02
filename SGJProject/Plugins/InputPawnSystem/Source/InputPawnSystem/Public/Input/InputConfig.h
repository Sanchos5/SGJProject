// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputConfig.generated.h"

class UInputAction;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTaggedInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputTag")
	FGameplayTag InputTag;
};

UCLASS(BlueprintType, Const)
class INPUTPAWNSYSTEM_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UInputConfig(const FObjectInitializer& ObjectInitializer);

	// Returns the first Input Action associated with a given tag.
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag) const;

public:
	// List of input actions used by the owner. These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NativeInputAction")
	TArray<FTaggedInputAction> NativeInputActions;
};
