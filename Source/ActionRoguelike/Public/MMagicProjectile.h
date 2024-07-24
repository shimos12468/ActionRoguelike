// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBaseProjectile.h"
#include "MMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticaleSystemComponent;
UCLASS()
class ACTIONROGUELIKE_API AMMagicProjectile : public AMBaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMMagicProjectile();
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	
	UPROPERTY(EditAnywhere)
	UParticleSystem* EmittingEffect;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
