// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "MSaveGame.h"

void AMPlayerState::AddCredit(int Amount)
{
	PlayerCredits += Amount;
	OnCreditsChanged.Broadcast(this, PlayerCredits, Amount);
}

void AMPlayerState::RemoveCredit(int Amount)
{
	PlayerCredits -= Amount;
	OnCreditsChanged.Broadcast(this, PlayerCredits, -Amount);
}

void AMPlayerState::OnRep_Credits(int NewCredits)
{
	OnCreditsChanged.Broadcast(this, NewCredits, NewCredits-PlayerCredits);
}

int AMPlayerState::GetCredit()
{
	return PlayerCredits;
}
void AMPlayerState::SavePlayerState_Implementation(UMSaveGame* CurrentSaveGame)
{
	if (CurrentSaveGame)
	{
		CurrentSaveGame->Credits = PlayerCredits;
	}
}

void AMPlayerState::LoadPlayerState_Implementation(UMSaveGame* CurrentSaveGame)
{
	if (CurrentSaveGame)
	{
		AddCredit(CurrentSaveGame->Credits);
	}
}
void AMPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPlayerState, PlayerCredits);
	
}

