// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MTargetDummy.generated.h"

class UMAttributeComponent;
UCLASS()
class ACTIONROGUELIKE_API AMTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMTargetDummy();

protected:
	
	UPROPERTY(VisibleAnywhere)
	UMAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,UMAttributeComponent* OwningComp,float NewHealth,float Delta);
};
