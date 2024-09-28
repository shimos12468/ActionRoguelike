// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGameplayInterface.h"
#include "MInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UMInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PrimaryInteract();
public:	
	// Sets default values for this component's properties
	UMInteractionComponent();


		
};
