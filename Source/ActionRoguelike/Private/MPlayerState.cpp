// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerState.h"


void AMPlayerState::AddCredit(AActor* CreditSource, int Amount)
{
	PlayerCredits += Amount;
	OnCreditsChanged.Broadcast(CreditSource, this->GetOwner(), PlayerCredits);
}

void AMPlayerState::RemoveCredit(AActor* CreditSource, int Amount)
{
	PlayerCredits -= Amount;

	OnCreditsChanged.Broadcast(CreditSource, this->GetOwner(), PlayerCredits);
}

int AMPlayerState::GetCredit()
{
	return PlayerCredits;
}
