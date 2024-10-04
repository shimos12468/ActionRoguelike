// Fill out your copyright notice in the Description page of Project Settings.


#include "MAction.h"

void UMAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT(" Running: %s"),*GetNameSafe(this));
}

void UMAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT(" Stopped: %s"), *GetNameSafe(this));

}

UWorld* UMAction::GetWorld() const
{
	UActorComponent*Comp = Cast<UActorComponent>(GetOuter());

	if (Comp) {
		return Comp->GetWorld();
	}
	return nullptr;
}
