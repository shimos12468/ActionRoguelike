// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" 
#include "MPowerup.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AMPowerup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPowerup();

	void Deactivate();
	void Activate();
protected:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMeshComponent* LidMesh;
	UPROPERTY(EditAnywhere)
	float DeactivationDuration;

};
