// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MAttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UMAttributeComponent*, OwningComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRageChanged, AActor*, InstigatorActor, UMAttributeComponent*, OwningComp, float, NewRage, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UMAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMAttributeComponent();
	UFUNCTION(BlueprintCallable,Category = "Attributes")
	static UMAttributeComponent* GetAttributies(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static bool IsActorAlive(AActor* Actor);


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Atributes")
	float MaxHealth;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category ="Atributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Atributes")
	float MaxRage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Atributes")
	float Rage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Atributes")
	float KilledCreditAmount;


	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	float GetHealth();


	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	float GetRage();


	UFUNCTION(BlueprintCallable)
	void RemoveRage(AActor* InstigatorActor ,float RageCost);
	
	UFUNCTION(BlueprintCallable)
	void AddRage(AActor* InstigatorActor,float RageAmount);
	
	
	UFUNCTION(BlueprintCallable)
	float GetMaxRage();

	UFUNCTION(BlueprintCallable)
	bool IsPlayerFullHealth();


	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnRageChanged OnRageChanged;

	UFUNCTION(BlueprintCallable ,Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor , float Delta);
};
