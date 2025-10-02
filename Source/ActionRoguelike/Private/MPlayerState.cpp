// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerState.h"
#include "Net/UnrealNetwork.h"

void AMPlayerState::AddCredit(AActor* CreditSource, int Amount)
{
	MulticastCreditsChanged_Implementation(CreditSource, Amount);
}

void AMPlayerState::RemoveCredit(AActor* CreditSource, int Amount)
{
	MulticastCreditsChanged_Implementation(CreditSource, -Amount);
}

void AMPlayerState::MulticastCreditsChanged_Implementation(AActor* InstigatorActor, int NewCredits)
{
	PlayerCredits += NewCredits;
	OnCreditsChanged.Broadcast(InstigatorActor, this->GetOwner(), PlayerCredits);
}

int AMPlayerState::GetCredit()
{
	return PlayerCredits;
}
void AMPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPlayerState, PlayerCredits);
	
}
