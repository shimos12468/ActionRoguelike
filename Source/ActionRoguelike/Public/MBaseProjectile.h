// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticaleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AMBaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMBaseProjectile();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* EffectComp;




};
