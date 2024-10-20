// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGameplayInterface.h"
#include "MInteractionComponent.generated.h"

class UMWorldUserWidget;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UMInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PrimaryInteract();

protected:

	void FindBestInteractable();

	virtual void BeginPlay()override;

	UPROPERTY()
	AActor* FocusedActor;
	
	UPROPERTY(EditDefaultsOnly,Category ="Trace")
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;
	

	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UMWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UMWorldUserWidget* DefaultWidgetInstance;

public:	


	virtual void TickComponent(float DeltaTime,ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Sets default values for this component's properties
	UMInteractionComponent();


		
};
