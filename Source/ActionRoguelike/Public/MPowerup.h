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

	FTimerHandle TimerHandle_DeactivateMesh;

protected:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(ReplicatedUsing = "OnRip_CoinConsumed", BlueprintReadOnly)
	bool Visiable;
		
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMeshComponent* LidMesh;
	UPROPERTY(EditAnywhere)
	float DeactivationDuration;
	

	UFUNCTION()
	void OnRip_CoinConsumed();
};
