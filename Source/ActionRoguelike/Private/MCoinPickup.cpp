// Fill out your copyright notice in the Description page of Project Settings.


#include "MCoinPickup.h"
#include "MAttributeComponent.h"
#include "MPlayerState.h"



void AMCoinPickup::Interact_Implementation(APawn* InstigatorPawn)
{

	UMAttributeComponent* Attributes = Cast<UMAttributeComponent>(InstigatorPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));
	if (Attributes) {

		if (!BaseMesh->IsVisible()) {

			
			return;
		}

		
		AMPlayerState* PS = InstigatorPawn->GetPlayerState<AMPlayerState>();
		
		
		GetWorldTimerManager().SetTimer(TimerHandle_DeactivateMesh, this, &AMCoinPickup::Activate, DeactivationDuration);
		if (PS) {

			PS->AddCredit(this, CreditAmount);
		}
		Deactivate();

		
	}

}



