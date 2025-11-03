// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BatteryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGJPROJECT_API UBatteryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBatteryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Battery")
	static UBatteryComponent* FindBatteryComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UBatteryComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable, Category = "Goggles System")
	void StartGogglesActivation();

	UFUNCTION(BlueprintCallable, Category = "Goggles System")
	void RemoveGoggles();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Goggles System")
	float ActivationProgress = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goggles Settings")
	float GogglesActivationTime = 5.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Goggles Settings")
	bool bIsActivating = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Goggles Settings")
	bool bGogglesEnabled = false;

public:

	UFUNCTION(BlueprintPure, Category = "Battery")
	float GetBatteryLevel() const { return CurrentBattery; }
	
private:

	void EnableGoggles();
	void DisableGoggles();

	UPROPERTY(EditAnywhere, Category = "BatterySettings", meta = (ClampMin = "0", ClampMax = "5"))
	int MaxBatteryLevel = 5;

	UPROPERTY(EditAnywhere, Category = "BatterySettings")
	int CurrentBattery = 5;
};
