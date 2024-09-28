// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGameplayInterface.h"
#include "Components/StaticMeshComponent.h" 

#include "MItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AMItemChest : public AActor ,public IMGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);
public:	
	// Sets default values for this actor's properties
	AMItemChest();

	

protected:

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

};
