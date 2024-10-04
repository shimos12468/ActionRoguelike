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
class UMActionComponent;
UCLASS()
class ACTIONROGUELIKE_API AMCharacter : public ACharacter
{
	GENERATED_BODY()
	
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

	UPROPERTY(VisibleAnywhere ,BlueprintReadOnly , Category = "Component")
	UMAttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMActionComponent* ActionComp;
	

	void MoveForward(float Value); 
	void MoveRight(float Value);
	

	void SprintStart();
	void SprintStop();
	
	void PrimaryAttack();
	void BlackHole();
	void Dash();

	void PrimaryInteract();
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	virtual void PostInitializeComponents()override;
	virtual void BeginPlay()override;

	virtual FVector GetPawnViewLocation()const override;

public:	



	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

	

};
