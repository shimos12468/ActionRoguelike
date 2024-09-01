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

bool UMAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UMAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}
