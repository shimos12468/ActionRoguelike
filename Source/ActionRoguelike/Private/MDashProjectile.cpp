// Fill out your copyright notice in the Description page of Project Settings.


#include "MDashProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MBaseProjectile.h"

AMDashProjectile::AMDashProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void AMDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComp->OnComponentHit.AddDynamic(this, &AMDashProjectile::OnHit);
	GetWorldTimerManager().SetTimer(EmittEffect_TimeHandler, this, &AMDashProjectile::EmitteEffect_TimeElapsed, 0.2);
}

void AMDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}
	

void AMDashProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	if (OtherActor != GetInstigator()) {
		GetWorldTimerManager().ClearTimer(EmittEffect_TimeHandler);
		MovementComp->Velocity = FVector(0, 0, 0);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmittingEffect, GetActorLocation(), GetActorRotation());
		if (EffectComp) {
			EffectComp->DestroyComponent();
		}
		GetWorldTimerManager().SetTimer(TeleportInstigator_TimeHandler, this, &AMDashProjectile::TeleportInstigator_TimeElapsed, 0.2);
	}
}


void AMDashProjectile::EmitteEffect_TimeElapsed()
{
	GetWorldTimerManager().ClearTimer(EmittEffect_TimeHandler);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmittingEffect, GetActorLocation(), GetActorRotation());
	MovementComp->Velocity = FVector(0,0,0);
	if (EffectComp) {
		EffectComp->DestroyComponent();
	}
	GetWorldTimerManager().SetTimer(TeleportInstigator_TimeHandler, this, &AMDashProjectile::TeleportInstigator_TimeElapsed, 0.2);
}

void AMDashProjectile::TeleportInstigator_TimeElapsed()
{
	GetWorldTimerManager().ClearTimer(TeleportInstigator_TimeHandler);
	GetInstigator()->TeleportTo(GetActorLocation(),GetInstigator()->GetActorRotation(),false,false);

}

void AMDashProjectile::Tick(float DeltaTime)
{
	PrimaryActorTick.bCanEverTick = true;
}
