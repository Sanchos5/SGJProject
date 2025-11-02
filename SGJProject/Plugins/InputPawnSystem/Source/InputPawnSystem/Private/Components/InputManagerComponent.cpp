// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputManagerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UInputManagerComponent::UInputManagerComponent(const FObjectInitializer& ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
	
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextObject(
		TEXT("/InputPawnSystem/Input/IMC_DefaultKey"));
	if (InputMappingContextObject.Succeeded())
	{
		InputMappingContext = InputMappingContextObject.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load InputMappingContextObject"));
	}
	
}

// Called when the game starts
void UInputManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if(OwnerPawn && OwnerPawn->IsPlayerControlled())
	{
		if(APlayerController* PC = OwnerPawn->GetController<APlayerController>())
		{
			if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	
}