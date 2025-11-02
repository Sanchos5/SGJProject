// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UAnimBlueprint;
class UInputPawnComponent;

UCLASS()
class SGJPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Offset for the first-person camera
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector FirstPersonCameraOffset = FVector(2.8f, 5.9f, 0.0f);

	// First-person camera field of view
	UPROPERTY(EditAnywhere, Category = "Camera")
	float FirstPersonFieldOfView = 70.0f;
 
	// First-person camera view scale
	UPROPERTY(EditAnywhere, Category = "Camera")
	float FirstPersonScale = 0.6f;

	// First Person animations
	UPROPERTY(EditAnywhere, Category = Animation)
	UAnimBlueprint* FirstPersonDefaultAnim;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FPCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputPawnComponent> InputPawn;
};
