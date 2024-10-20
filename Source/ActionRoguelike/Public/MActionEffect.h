// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAction.h"
#include "MActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMActionEffect : public UMAction
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Effect")
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float Period;


	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintNativeEvent,Category = "Effect")
	void ExcutePeriodicEffect(AActor* Instigator);

public:


	void StartAction_Implementation(AActor* Instigator) override;
	void StopAction_Implementation(AActor* Instigator) override;

	UMActionEffect();
};
