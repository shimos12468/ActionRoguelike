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
UCLASS()
class ACTIONROGUELIKE_API AMAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMAICharacter();

protected:
	
	UMWorldUserWidget* ActiveWidget;
	
	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;


	UPROPERTY(EditAnywhere , Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Components")
	UMAttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMActionComponent* ActionComp;

	UFUNCTION()
	void SetTargetActor(AActor* TargetActor);

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	virtual void PostInitializeComponents() override;
	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta);
};
