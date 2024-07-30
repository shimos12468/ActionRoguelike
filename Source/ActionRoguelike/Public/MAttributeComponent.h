// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UMAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMAttributeComponent();

protected:

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category ="Atributes")
	float Health;
public:

	UFUNCTION(BlueprintCallable ,Category = "Attributes")
	bool ApplyHealthChange(float Delta);
};
