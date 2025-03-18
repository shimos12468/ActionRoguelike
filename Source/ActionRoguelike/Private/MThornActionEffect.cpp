// Fill out your copyright notice in the Description page of Project Settings.


#include "MThornActionEffect.h"
#include "MAttributeComponent.h"
#include "MAction.h"
#include "MActionComponent.h"

UMThornActionEffect::UMThornActionEffect()
{
	bIsAutoStart = true;
}

void UMThornActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	UMAttributeComponent* AttributeComp = UMAttributeComponent::GetAttributies(Instigator);
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.AddDynamic(this, &UMThornActionEffect::OnHealthChanged);
	}
}

void UMThornActionEffect::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	UMActionComponent* ActionComp= GetOwningComponent();

	AActor* TargetActor = ActionComp->GetOwner();

	UMAttributeComponent* attrubute = UMAttributeComponent::GetAttributies(InstigatorActor);
	const int DamageBack = FMath::CeilToInt(Delta/2);
	
	attrubute->ApplyHealthChange(TargetActor,DamageBack);
}

void UMThornActionEffect::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	
	UMAttributeComponent* AttributeComp = UMAttributeComponent::GetAttributies(Instigator);
	
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &UMThornActionEffect::OnHealthChanged);
	}
	
}
