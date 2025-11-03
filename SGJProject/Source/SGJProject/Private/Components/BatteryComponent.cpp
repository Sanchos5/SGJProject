// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BatteryComponent.h"

// Sets default values for this component's properties
UBatteryComponent::UBatteryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBatteryComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UBatteryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBatteryComponent::StartGogglesActivation()
{
	if (bGogglesEnabled || bIsActivating) return;

	if (CurrentBattery <= 0)
	{
		return;
	}

	if (ActivationProgress <= GogglesActivationTime)
	{
		ActivationProgress += 1.0f * GetWorld()->DeltaTimeSeconds;
	}
	else
	{
		EnableGoggles();
	}
}

void UBatteryComponent::RemoveGoggles()
{
	ActivationProgress = 0.0f;
	if (!bGogglesEnabled) return;
	
	DisableGoggles();
}

void UBatteryComponent::EnableGoggles()
{
	if (bGogglesEnabled) return;

	bIsActivating = true;
	ActivationProgress = 0.0f;
	bGogglesEnabled = true;
	CurrentBattery -= 1;
}

void UBatteryComponent::DisableGoggles()
{
	if (!bGogglesEnabled) return;

	bIsActivating = false;
	bGogglesEnabled = false;
}

