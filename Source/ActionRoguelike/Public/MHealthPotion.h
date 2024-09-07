// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPowerup.h"
#include "MGameplayInterface.h"
#include "MHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AMHealthPotion : public AMPowerup , public IMGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float HealthAmount;

	FTimerHandle TimerHandle_DeactivateMesh;

};
