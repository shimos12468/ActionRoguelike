// Fill out your copyright notice in the Description page of Project Settings.


#include "MAction_ProjectileAttack.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "Particles/ParticleSystem.h"
#include "MAttributeComponent.h"
UMAction_ProjectileAttack::UMAction_ProjectileAttack()
{
	AttackAnimDelay = 0.2f;
	HandSocketName = "Muzzle_01";
	RageCost = 0;
}

void UMAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);

	if (Character) {


		UMAttributeComponent* AttributeComp = UMAttributeComponent::GetAttributies(Instigator);


		if (AttributeComp->GetRage() < RageCost) {
			
			StopAction(Instigator);;
			
			return;
		}
		AttributeComp->RemoveRage(Instigator,RageCost);
		Character->PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(SpawnVFX, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;

		Delegate.BindUFunction(this, "AttackDelay_TimeElapsed", Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
}


void UMAction_ProjectileAttack::AttackDelay_TimeElapsed(ACharacter* InstigatorCharacter)
{
	if (ensure(ProjectileClass)) {

		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;

		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20);


		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjectParams;

		ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);

		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
		FVector TraceEnd = TraceStart+ (InstigatorCharacter->GetControlRotation().Vector() * 5000);

		FHitResult Hit;

		bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectParams, Shape, Params);

		if (bBlockingHit) {

			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjectionRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjectionRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	}
	StopAction(InstigatorCharacter);
}

