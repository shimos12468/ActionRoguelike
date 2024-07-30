// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MBaseProjectile.h"
#include "MDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AMDashProjectile : public AMBaseProjectile
{
	GENERATED_BODY()
	

public:
	AMDashProjectile();
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:

	FTimerHandle EmittEffect_TimeHandler;
	FTimerHandle TeleportInstigator_TimeHandler;
	UPROPERTY(EditAnywhere)
	UParticleSystem* EmittingEffect;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

	void EmitteEffect_TimeElapsed();
	void TeleportInstigator_TimeElapsed();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
