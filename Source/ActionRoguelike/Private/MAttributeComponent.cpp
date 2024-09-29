// Fill out your copyright notice in the Description page of Project Settings.


#include "MAttributeComponent.h"

// Sets default values for this component's properties
UMAttributeComponent::UMAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	MaxHealth = 100;
	Health = MaxHealth;
}

bool UMAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}

bool UMAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}



float UMAttributeComponent::GetHealth()
{
	return Health;
}

float UMAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}

bool UMAttributeComponent::IsPlayerFullHealth()
{
	return Health == MaxHealth;
}

bool UMAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged()) {
		return false;
	}

	float OldHealth = Health;
	Health += Delta;
	Health= FMath::Clamp(Health,0.0f,MaxHealth);
	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta!=0;
}

UMAttributeComponent* UMAttributeComponent::GetAttributies(AActor* FromActor)
{
	if (FromActor) {

		return Cast<UMAttributeComponent>(FromActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool UMAttributeComponent::IsActorAlive(AActor* Actor)
{
	UMAttributeComponent* Attributies = GetAttributies(Actor);

	if (Attributies) {
		return Attributies->IsAlive();
	}
	return false;
}
