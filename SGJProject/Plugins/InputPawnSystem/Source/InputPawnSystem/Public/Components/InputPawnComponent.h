// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputManagerComponent.h"
#include "InputPawnComponent.generated.h"

class UInputComponent;
class UInputConfig;
struct FInputActionValue;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INPUTPAWNSYSTEM_API UInputPawnComponent : public UInputManagerComponent
{
	GENERATED_BODY()

public:

	UInputPawnComponent(const FObjectInitializer& ObjectInitializer);

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditAnywhere, Category = "Input|IC")
	TObjectPtr<UInputConfig> InputConfig;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);
	void Input_Fire(const FInputActionValue& InputActionValue);
};
