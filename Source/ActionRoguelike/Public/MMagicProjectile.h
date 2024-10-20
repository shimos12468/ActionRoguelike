// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBaseProjectile.h"
#include "MProjectileBase.h"
#include "GameplayTagContainer.h"
#include "MMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticaleSystemComponent;
class UMActionEffect;
UCLASS()
class ACTIONROGUELIKE_API AMMagicProjectile : public AMProjectileBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageAmount = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UMActionEffect>BurningActionClass;
	
	UFUNCTION()
	void ApplyDamage(const FHitResult& Hit, AActor* OwnerActor, AActor* OtherActor);

	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	
public:	
	
	// Sets default values for this actor's properties
	AMMagicProjectile();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
};
