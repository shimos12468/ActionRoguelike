// Fill out your copyright notice in the Description page of Project Settings.


#include "MDashProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MBaseProjectile.h"

AMDashProjectile::AMDashProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	MovementComp->InitialSpeed = 6000;
}

void AMDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(EmittEffect_TimeHandler, this, &AMDashProjectile::Explode, 0.2);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

}

void AMDashProjectile::TeleportInstigator_TimeElapsed()
{
	GetInstigator()->TeleportTo(GetActorLocation(),GetInstigator()->GetActorRotation(),false,false);

}

void AMDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(EmittEffect_TimeHandler);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	MovementComp->StopMovementImmediately();

	SetActorEnableCollision(false);
	
	if (EffectComp) {
		EffectComp->DeactivateSystem();
	}
	
	FTimerHandle TeleportInstigator_TimeHandler;
	GetWorldTimerManager().SetTimer(TeleportInstigator_TimeHandler, this, &AMDashProjectile::TeleportInstigator_TimeElapsed, 0.2);
}
