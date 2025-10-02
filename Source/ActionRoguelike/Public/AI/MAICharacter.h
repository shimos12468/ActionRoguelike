// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MAICharacter.generated.h"

class UMAttributeComponent;
class UPawnSensingComponent;
class UUserWidget;
class UMWorldUserWidget;
class UMActionComponent;
class AAIController;
UCLASS()
class ACTIONROGUELIKE_API AMAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMAICharacter();

protected:
	
	UMWorldUserWidget* ActiveWidget;

	UMWorldUserWidget* SpottedPlayerWidget;
	
	
	AAIController* AIController;
	
	
	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UUserWidget>playerSpottedWidgetClass;

	UPROPERTY(EditAnywhere , Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Components")
	UMAttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float ActivationDuration;
	

	
	
	AActor* TargetActor;

	FTimerHandle TimerHandle_DeactivateSpottedPlayerWidget;

	UFUNCTION()
	void SetTargetActor(AActor* NewTargetActor);

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void DeactivateSpottedPlayerWidget();

	UFUNCTION()
	AActor* GetTargetActor();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPawnSeen();

};
