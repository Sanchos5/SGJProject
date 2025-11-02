// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputPawnComponent.h"
#include "Input/GameInputComponent.h"
#include "Input/InputConfig.h"
#include "InputGameplayTags.h"
#include "GameFramework/Character.h"

UInputPawnComponent::UInputPawnComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	
	static ConstructorHelpers::FObjectFinder<UInputConfig> InputConfigObject(
		TEXT("/InputPawnSystem/Input/Configs/InputData_Player"));
	if(InputConfigObject.Succeeded())
	{
		InputConfig = InputConfigObject.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load InputConfigObject"));
	}
	
}

// Called when the game starts
void UInputPawnComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn && OwnerPawn->IsLocallyControlled())
	{
		SetupPlayerInputComponent(OwnerPawn->InputComponent);
	}

	
}

void UInputPawnComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UGameInputComponent* Input = Cast<UGameInputComponent>(PlayerInputComponent))
	{
		Input->BindNativeAction(InputConfig, GameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		Input->BindNativeAction(InputConfig, GameplayTags::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse);
		Input->BindNativeAction(InputConfig, GameplayTags::InputTag_Jump, ETriggerEvent::Started, this, &ThisClass::Input_Jump);
		Input->BindNativeAction(InputConfig, GameplayTags::InputTag_Crouch, ETriggerEvent::Started, this, &ThisClass::Input_Crouch);
		Input->BindNativeAction(InputConfig, GameplayTags::InputTag_Fire, ETriggerEvent::Started, this, &ThisClass::Input_Fire);
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	UE_LOG(LogTemp, Warning, TEXT("InitializePlayerInput: Pawn=%s, IsLocallyControlled=%d, InputComponent=%p"),
		*GetNameSafe(OwnerPawn),
		OwnerPawn ? OwnerPawn->IsLocallyControlled() : -1,
		PlayerInputComponent);
}

void UInputPawnComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* Contoller = OwnerPawn ? OwnerPawn->GetController() : nullptr;

	if (Contoller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, OwnerPawn->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			OwnerPawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			OwnerPawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UInputPawnComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* Contoller = OwnerPawn ? OwnerPawn->GetController() : nullptr;

	if (Contoller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();

		if (Value.X != 0.0f)
		{
			OwnerPawn->AddControllerYawInput(Value.X);
		}
		if (Value.Y != 0.0f)
		{
			OwnerPawn->AddControllerPitchInput(Value.Y);
		}
	}
}

void UInputPawnComponent::Input_Jump(const FInputActionValue& InputActionValue)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character)
	{
		Character->Jump();
	}
}

void UInputPawnComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	bool bIsCrouched = Character ? Character->bIsCrouched : false;

	if (Character)
	{
		if(!bIsCrouched)
		{
			bIsCrouched = true;
			Character->Crouch();
		}
		else
		{
			bIsCrouched = false;
			Character->UnCrouch();
		}
	}
}

void UInputPawnComponent::Input_Fire(const FInputActionValue& InputActionValue)
{
	//Do nothing
	
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}
