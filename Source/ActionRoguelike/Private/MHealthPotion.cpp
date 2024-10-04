// Fill out your copyright notice in the Description page of Project Settings.


#include "MHealthPotion.h"
#include "MAttributeComponent.h"
#include "MPlayerState.h"

void AMHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{

	UMAttributeComponent* Attributes =UMAttributeComponent::GetAttributies(InstigatorPawn);
	AMPlayerState* PS = InstigatorPawn->GetPlayerState<AMPlayerState>();
	if (Attributes&&PS) {

		if (!BaseMesh->IsVisible()|| Attributes->IsPlayerFullHealth())
			return;

		if (PS->GetCredit()< Cost) {


			UE_LOG(LogTemp, Warning, TEXT("Buddy you are poor af"));
			return;
		}


		GetWorldTimerManager().SetTimer(TimerHandle_DeactivateMesh, this, &AMHealthPotion::Activate, DeactivationDuration);
		Attributes->ApplyHealthChange(this , HealthAmount);
		
		PS->RemoveCredit(this, Cost);


		Deactivate();
	}
}
