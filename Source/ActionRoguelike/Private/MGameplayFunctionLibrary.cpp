// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameplayFunctionLibrary.h"
#include "MAttributeComponent.h"

bool UMGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UMAttributeComponent* AttributeComp = UMAttributeComponent::GetAttributies(TargetActor);
	if(AttributeComp) {

		return AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;
}

bool UMGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& Hit)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount)) {


		 UPrimitiveComponent* HitComp= Hit.GetComponent();
		 if (HitComp && HitComp->IsSimulatingPhysics(Hit.BoneName)) {

			 HitComp->AddImpulseAtLocation(-Hit.ImpactNormal * 300000.0f, Hit.ImpactPoint, Hit.BoneName);
		 }


		return true;
	}
	return false;
}
