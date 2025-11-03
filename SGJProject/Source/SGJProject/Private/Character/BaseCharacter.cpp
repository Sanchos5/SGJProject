// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputPawnComponent.h"
#include "Components/BatteryComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//USkeletalMeshComponent* MeshComp = GetMesh();
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;
	
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FirstPersonMesh");
	check(FirstPersonMesh);
	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetOnlyOwnerSee(true);
	
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	check(FPCameraComponent);
	FPCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FPCameraComponent->bUsePawnControlRotation = true;
	FPCameraComponent->SetRelativeLocationAndRotation(FirstPersonCameraOffset, FRotator(0, 90.0f, -90.0f));
	FPCameraComponent->bEnableFirstPersonFieldOfView = true;
	FPCameraComponent->bEnableFirstPersonScale = true;
	FPCameraComponent->FirstPersonFieldOfView = FirstPersonFieldOfView;
	FPCameraComponent->FirstPersonScale = FirstPersonScale;
	
	InputPawn = CreateDefaultSubobject<UInputPawnComponent>("InputComponent");

	BatteryComponent = CreateDefaultSubobject<UBatteryComponent>("BatteryComponent");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set the animations on the first person mesh.
	FirstPersonMesh->SetAnimInstanceClass(FirstPersonDefaultAnim->GeneratedClass);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}