// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MProjectileBase.h"
#include "MDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AMDashProjectile : public AMProjectileBase
{
	GENERATED_BODY()
	

public:
	AMDashProjectile();
	
protected:

	FTimerHandle EmittEffect_TimeHandler;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TeleportInstigator_TimeElapsed();

	virtual void Explode_Implementation()override;


};
