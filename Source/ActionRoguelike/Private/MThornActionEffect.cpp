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
	AttributeComp->OnHealthChanged.AddDynamic(this, &UMThornActionEffect::OnHealthChanged);
	if (Duration > 0.0f) {
		FTimerDelegate Delegate;

		Delegate.BindUFunction(this, "StopAction", Instigator);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);

	}

	if (Period > 0.0f) {

		FTimerDelegate Delegate;

		Delegate.BindUFunction(this, "ExcutePeriodicEffect", Instigator);

		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}
}

void UMThornActionEffect::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	UMActionComponent* ActionComp= GetOwningComponent();

	AActor* TargetActor = ActionComp->GetOwner();

	UMAttributeComponent* attrubute = UMAttributeComponent::GetAttributies(InstigatorActor);
	const int DamageBack = FMath::CeilToInt(Delta/5);
	
	attrubute->ApplyHealthChange(TargetActor,DamageBack);
}

void UMThornActionEffect::StopAction_Implementation(AActor* Instigator)
{
	UMAttributeComponent* AttributeComp = UMAttributeComponent::GetAttributies(Instigator);
	
	AttributeComp->OnHealthChanged.RemoveDynamic(this, &UMThornActionEffect::OnHealthChanged);
	
	Super::StopAction_Implementation(Instigator);
}
