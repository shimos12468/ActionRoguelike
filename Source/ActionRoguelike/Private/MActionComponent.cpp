// Fill out your copyright notice in the Description page of Project Settings.


#include "MActionComponent.h"
#include "MAction.h"
#include "../ActionRoguelike.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"


UMActionComponent::UMActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	SetIsReplicatedByDefault(true);
	// ...
}



void UMActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority()) {
		for (TSubclassOf<UMAction>ActionClass : DefaultActions) {

			AddAction(GetOwner(), ActionClass);
		}
	}
	
}



void UMActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMsg = GetNameSafe(GetOwner()) + "  :  " + ActiveGameplayTags.ToStringSimple();
	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::White, DebugMsg);
	// ...

	for (UMAction* Action : Actions) {
		FColor TextColor = Action->IsRunning() ? FColor::Blue : FColor::White;

		FString ActionMsg = FString::Printf(TEXT("[%s] Action: %s : IsRunning: %s : Outer: %s"),
			*GetNameSafe(GetOwner()),
			*Action->ActionName.ToString(),
			Action->IsRunning() ? TEXT("true") : TEXT("false"),
			*GetNameSafe(Action->GetOuter()));

		LogOnScreen(this, ActionMsg, TextColor, 0.0f);
	}
}

void UMActionComponent::AddAction(AActor* Instigator ,TSubclassOf<UMAction> ActionClass)
{
	if (!ensure(ActionClass)) {
		return;
	}

	UMAction* NewAction = NewObject<UMAction>(GetOwner(), ActionClass);
	bool bAddAction = true;
	for(UMAction* var : Actions)
	{
		if (var->ActionName == NewAction->ActionName) {
			bAddAction = false;
			break;
		}
	}


	if (ensure(NewAction) &&bAddAction ) {

		NewAction->Initialize(this);
		Actions.Add(NewAction);

		if (NewAction->bIsAutoStart&&ensure(NewAction->CanStart(Instigator))) {

			NewAction->StartAction(Instigator);
		}

	}


}

void UMActionComponent::RemoveAction(UMAction* Action)
{
	if (!ensure(Action && !Action->IsRunning())) {
		return;
	}

	Actions.Remove(Action);
}

bool UMActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UMAction* Action : Actions) {

		if (Action && Action->ActionName == ActionName) {

			if (!Action->CanStart(Instigator)) {

				FString DebugMsg = GetNameSafe(GetOwner()) + "  :  " + ActiveGameplayTags.ToStringSimple();
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);

				continue;
			}

			if (!GetOwner()->HasAuthority()) {

				ServerStartAction(Instigator, ActionName);
			}
			
			Action->StartAction(Instigator);
			

			return true;
		}
	}
	return false;
}




bool UMActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{

	for (UMAction* Action : Actions) {

		if (Action && Action->ActionName == ActionName) {

			if (!Action->IsRunning()) {
				continue;
			}

			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;

}

TArray<UMAction*> UMActionComponent::GetActionsList()
{
	return Actions;
	
}

void UMActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName Action)
{
	StartActionByName(Instigator, Action);
}


void UMActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMActionComponent, Actions);
}
bool UMActionComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (UMAction* Action : Actions) {
		
		if (Action) {
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;

}

