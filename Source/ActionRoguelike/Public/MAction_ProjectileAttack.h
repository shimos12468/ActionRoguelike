// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAction.h"
#include "MAction_ProjectileAttack.generated.h"

/**
 * 
 */
class UAnimMontage;
class UParticleSystem;
UCLASS()
class ACTIONROGUELIKE_API UMAction_ProjectileAttack : public UMAction
{
	GENERATED_BODY()




protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
		FName HandSocketName;

	UPROPERTY(EditAnywhere, Category = "Attack")
		float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* SpawnVFX;
	UFUNCTION()
		void AttackDelay_TimeElapsed(ACharacter* InstigatorCharacter);


public:	

	virtual void StartAction_Implementation(AActor* Instigator) override;
	
	UMAction_ProjectileAttack();

};
