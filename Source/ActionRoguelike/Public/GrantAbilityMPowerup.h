// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPowerup.h"
#include "MGameplayInterface.h"
#include "GrantAbilityMPowerup.generated.h"

/**
 * 
 */
class UMAction;
UCLASS()
class ACTIONROGUELIKE_API AGrantAbilityMPowerup : public AMPowerup, public IMGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TSubclassOf<UMAction> ActionToAdd;



};
