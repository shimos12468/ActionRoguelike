// Fill out your copyright notice in the Description page of Project Settings.


#include "MActionComponent.h"
#include "MAction.h"


UMActionComponent::UMActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UMActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UMAction>ActionClass : DefaultActions) {

		AddAction(ActionClass);
	}
	
}



void UMActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMActionComponent::AddAction(TSubclassOf<UMAction> ActionClass)
{
	if (!ensure(ActionClass)) {
		return;
	}

	UMAction* NewAction = NewObject<UMAction>(this, ActionClass);
	if (ensure(NewAction)) {

		Actions.Add(NewAction);
	}


}

bool UMActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UMAction* Action : Actions) {

		if (Action && Action->ActionName == ActionName) {

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

			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;

}

