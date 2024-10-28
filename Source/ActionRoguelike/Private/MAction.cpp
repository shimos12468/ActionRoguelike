// Fill out your copyright notice in the Description page of Project Settings.


#include "MAction.h"
#include "MActionComponent.h"
#include "../ActionRoguelike.h"
#include "Net/UnrealNetwork.h"



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
	//UE_LOG(LogTemp, Warning, TEXT(" Running: %s"),*GetNameSafe(this));

	LogOnScreen(this, FString::Printf(TEXT("Started: %s"),*ActionName.ToString()), FColor::Green);
	UMActionComponent* ActionComp = GetOwningComponent();

	ActionComp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning = true;
}

void UMAction::StopAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp, Warning, TEXT(" Stopped: %s"), *GetNameSafe(this));
	LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::White);
	//ensureAlways(bIsRunning);
	
	UMActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}

UWorld* UMAction::GetWorld() const
{
	AActor*Actor = Cast<AActor>(GetOuter());

	if (Actor) {
		return Actor->GetWorld();
	}
	return nullptr;
}
UMActionComponent* UMAction::GetOwningComponent() const
{
	return ActionComponent;

}

void UMAction::Initialize(UMActionComponent* NewActionComp)
{
	ActionComponent = NewActionComp;
}

void UMAction::OnRip_IsRunning()
{
	if (bIsRunning) {

		StartAction(nullptr);
	}
	else {
		StopAction(nullptr);
	}
}

bool UMAction::IsRunning() const
{
	return bIsRunning;
}

FName UMAction::GetActionName()
{
	return ActionName;
}


void UMAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMAction, bIsRunning);
	DOREPLIFETIME(UMAction, ActionComponent);
}
