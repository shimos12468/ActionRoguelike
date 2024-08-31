// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MProjectileBase.generated.h"
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class USoundCue;
UCLASS(ABSTRACT)
class ACTIONROGUELIKE_API AMProjectileBase : public AActor
{
	GENERATED_BODY()
protected:


	UPROPERTY(EditDefaultsOnly,Category="Effects")
	UParticleSystem* ImpactVFX; 
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* ImpactSound;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere ,Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	UAudioComponent* FlightSoundComponent;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* EffectComp;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Explode();
	
	virtual void PostInitializeComponents() override;

public:
	// Sets default values for this actor's properties
	AMProjectileBase();
};
