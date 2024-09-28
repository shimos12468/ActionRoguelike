// Fill out your copyright notice in the Description page of Project Settings.


#include "MHealthPotion.h"
#include "MAttributeComponent.h"

void AMHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{

	UMAttributeComponent* Attributes = Cast<UMAttributeComponent>(InstigatorPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));
	if (Attributes) {

		if (!BaseMesh->IsVisible()|| Attributes->IsPlayerFullHealth())
			return;

		GetWorldTimerManager().SetTimer(TimerHandle_DeactivateMesh, this, &AMHealthPotion::Activate, DeactivationDuration);
		Attributes->ApplyHealthChange(this , HealthAmount);
		Deactivate();
	}
}
