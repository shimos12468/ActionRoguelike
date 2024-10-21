// Fill out your copyright notice in the Description page of Project Settings.


#include "MAction.h"
#include "MActionComponent.h"



bool UMAction::CanStart_Implementation(AActor* Instigator)
{

	if (IsRunning()) {

		return false;
	}

	UMActionComponent* ActionComp = GetOwningComponent();

	if (ActionComp->ActiveGameplayTags.HasAny(BlockedTags)) {
		return false;
	}

	return true;
}

void UMAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT(" Running: %s"),*GetNameSafe(this));

	UMActionComponent* ActionComp = GetOwningComponent();

	ActionComp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning = true;
}

void UMAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT(" Stopped: %s"), *GetNameSafe(this));
	
	ensureAlways(bIsRunning);
	
	UMActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}

UWorld* UMAction::GetWorld() const
{
	UActorComponent*Comp = Cast<UActorComponent>(GetOuter());

	if (Comp) {
		return Comp->GetWorld();
	}
	return nullptr;
}
UMActionComponent* UMAction::GetOwningComponent() const
{
	return Cast<UMActionComponent>(GetOuter());

}
bool UMAction::IsRunning() const
{
	return bIsRunning;
}

FName UMAction::GetActionName()
{
	return ActionName;
}

