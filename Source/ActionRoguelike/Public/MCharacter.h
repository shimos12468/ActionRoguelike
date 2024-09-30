// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"
class UCameraComponent;
class USpringArmComponent;
class UMInteractionComponent;
class UAnimMontage;
class UMAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass2;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Ability")
	TSubclassOf<AActor> PrimaryAbilityProjectile;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* SpawnVFX;

	FTimerHandle TimerHandle_PrimaryAttrack;

	FTimerHandle TimerHandle_SecondaryAttrack;
	
	FTimerHandle TimerHandle_PrimaryAbility;

public:
	// Sets default values for this character's properties
	AMCharacter();

protected:


	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UMInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere ,BlueprintReadOnly)
	UMAttributeComponent* AttributeComp;

	

	void MoveForward(float Value); 
	
	void MoveRight(float Value);
	
	void PrimaryAttack();
	
	void PrimaryAttack_TimeElapsed();
	
	void SecondaryAttack();

	void SecondaryAttack_TimeElapsed();

	void PrimaryAbility();

	void PrimaryAbility_TimeElapsed();

	void PrimaryInteract();


	virtual void PostInitializeComponents()override;

	virtual FVector GetPawnViewLocation()const override;

public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta);

};
