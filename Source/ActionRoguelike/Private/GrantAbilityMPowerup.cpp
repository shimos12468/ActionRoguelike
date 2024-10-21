// Fill out your copyright notice in the Description page of Project Settings.


#include "GrantAbilityMPowerup.h"
#include "MActionComponent.h"
#include "MAction.h"

void AGrantAbilityMPowerup::Interact_Implementation(APawn* InstigatorPawn)
{
	UMActionComponent* ActionComp = Cast<UMActionComponent>(InstigatorPawn->GetComponentByClass(UMActionComponent::StaticClass()));
	if (ActionComp) {


		if (!BaseMesh->IsVisible())
			return;

		
		

			ActionComp->AddAction(this, ActionToAdd);
			GetWorldTimerManager().SetTimer(TimerHandle_DeactivateMesh, this, &AGrantAbilityMPowerup::Activate, DeactivationDuration);
			Deactivate();
		

	}
}
