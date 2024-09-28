// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectileBase.h"
#include <Components/SphereComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
// Sets default values
AMProjectileBase::AMProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	


	RootComponent = SphereComp;
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	FlightSoundComponent = CreateDefaultSubobject<UAudioComponent>("FlightSound");
	FlightSoundComponent->SetupAttachment(SphereComp);


	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0;
	MovementComp->InitialSpeed = 8000;

}

void AMProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AMProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &AMProjectileBase::OnActorHit);
	
}

void AMProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	FlightSoundComponent->Play();
}

void AMProjectileBase::Explode_Implementation() {


	if (ensure(!IsPendingKill())) {

		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		Destroy();

	}

}


