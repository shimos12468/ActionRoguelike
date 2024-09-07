// Fill out your copyright notice in the Description page of Project Settings.


#include "MAttributeComponent.h"

// Sets default values for this component's properties
UMAttributeComponent::UMAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	MaxHealth = 100;
	Health = MaxHealth;
	Damage = 20;
}

bool UMAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float UMAttributeComponent::GetDamage()
{
	return Damage;
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

bool UMAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	Health= FMath::Clamp(Health,0.0f,MaxHealth);
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}
