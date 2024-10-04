// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPowerup.h"
#include "MGameplayInterface.h"
#include "MCoinPickup.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AMCoinPickup : public AMPowerup , public IMGameplayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float CreditAmount;
		
	
	void Interact_Implementation(APawn* InstigatorPawn);
	
	


};
