// Fill out your copyright notice in the Description page of Project Settings.


#include "MActionEffect.h"
#include "MActionComponent.h"





UMActionEffect::UMActionEffect()
{
	bIsAutoStart = true;
	
}


float UMActionEffect::GetTimeRemaining() const
{
	float EndTime = TimeStarted+Duration;
	

	return EndTime - GetWorld()->TimeSeconds	;
}

void UMActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	if (Duration > 0.0f) {
		FTimerDelegate Delegate;

		Delegate.BindUFunction(this, "StopAction", Instigator);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);

	}

	if (Period > 0.0f)	{

		FTimerDelegate Delegate;

		Delegate.BindUFunction(this, "ExcutePeriodicEffect", Instigator);

		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}


}

void UMActionEffect::StopAction_Implementation(AActor* Instigator)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER) {

		ExcutePeriodicEffect(Instigator);
	}
	
	Super::StopAction_Implementation(Instigator);
	
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);

	UMActionComponent* ActionComp = GetOwningComponent();
	if (ActionComp) {
		
		ActionComp->RemoveAction(this);

	}
}

void UMActionEffect::ExcutePeriodicEffect_Implementation(AActor* Instigator)
{
	
	
}