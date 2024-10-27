// Fill out your copyright notice in the Description page of Project Settings.


#include "MActionComponent.h"
#include "MAction.h"


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

	for (TSubclassOf<UMAction>ActionClass : DefaultActions) {

		AddAction(GetOwner(), ActionClass);
	}
	
}



void UMActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + "  :  " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::White, DebugMsg);
	// ...
}

void UMActionComponent::AddAction(AActor* Instigator ,TSubclassOf<UMAction> ActionClass)
{
	if (!ensure(ActionClass)) {
		return;
	}

	UMAction* NewAction = NewObject<UMAction>(this, ActionClass);
	bool bAddAction = true;
	for(UMAction* var : Actions)
	{
		if (var->ActionName == NewAction->ActionName) {
			bAddAction = false;
			break;
		}
	}


	if (ensure(NewAction) &&bAddAction ) {
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

				ServerStartAction_Implementation(Instigator, ActionName);
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

void UMActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActionName)
{
	StartActionByName(Instigator, ActionName);
}

