// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBaseProjectile.h"
#include "MProjectileBase.h"
#include "MMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticaleSystemComponent;
UCLASS()
class ACTIONROGUELIKE_API AMMagicProjectile : public AMProjectileBase
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere,Category = "Attributes")
	float DamageAmount = 20;

	// Sets default values for this actor's properties
	AMMagicProjectile();
	
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
};
