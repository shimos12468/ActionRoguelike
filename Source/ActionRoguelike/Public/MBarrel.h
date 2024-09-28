// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" 
#include "PhysicsEngine/RadialForceComponent.h"
#include "MBarrel.generated.h"
UCLASS()
class ACTIONROGUELIKE_API AMBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMBarrel();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void Explode();

protected:
	virtual void PostInitializeComponents()override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere)
	URadialForceComponent* RadialForceComp;



};
