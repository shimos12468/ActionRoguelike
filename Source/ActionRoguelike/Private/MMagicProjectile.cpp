// Fill out your copyright notice in the Description page of Project Settings.


#include "MMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MAttributeComponent.h"
#include "Sound\SoundCue.h"
#include <Components/AudioComponent.h>
#include "MProjectileBase.h"
#include "MGameplayFunctionLibrary.h"
#include "MActionComponent.h"
#include "MActionEffect.h"
// Sets default values
AMMagicProjectile::AMMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void AMMagicProjectile::PostInitializeComponents() {

	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMMagicProjectile::OnActorOverlap);

}

// Called when the game starts or when spawned
void AMMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}


void AMMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerActor = GetInstigator();

	if (OtherActor && OtherActor != OwnerActor) {

		ApplyDamage(Hit, OwnerActor, OtherActor);
	}
}
void AMMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AActor* OwnerActor = GetInstigator();

	if (OtherActor && OtherActor != OwnerActor) {

		ApplyDamage(SweepResult, OwnerActor, OtherActor);

	}


}

void AMMagicProjectile::ApplyDamage(const FHitResult& Hit, AActor* OwnerActor, AActor* OtherActor)
{
	UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Hit.ImpactPoint);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeAsset, Hit.ImpactPoint, 500, 2000);
	
	UMActionComponent* ActionComp = Cast<UMActionComponent>(OtherActor->GetComponentByClass(UMActionComponent::StaticClass()));

	if (ActionComp&&ActionComp->ActiveGameplayTags.HasTag(ParryTag))
	{
		MovementComp->Velocity = -MovementComp->Velocity;

		SetInstigator(Cast<APawn>(OtherActor));
		return;
	}

	if (UMGameplayFunctionLibrary::ApplyDirectionalDamage(OwnerActor, OtherActor, DamageAmount, Hit)) {

		Explode();

		if (ActionComp&&HasAuthority()) {
			ActionComp->AddAction(GetInstigator(),BurningActionClass);
		}
	}
	Destroy(true);
}



