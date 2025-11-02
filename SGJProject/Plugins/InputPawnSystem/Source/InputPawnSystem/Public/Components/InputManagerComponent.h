// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "InputAction.h"
#include "InputManagerComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class ULocalPlayer;
class UInputMappingContext;

UCLASS()
class INPUTPAWNSYSTEM_API UInputManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputManagerComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Input|IMC")
	TObjectPtr<UInputMappingContext> InputMappingContext;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	
		
};
