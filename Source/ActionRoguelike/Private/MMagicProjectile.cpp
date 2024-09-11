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
// Sets default values
AMMagicProjectile::AMMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != GetInstigator()) {

		//UE_LOG(LogTemp, Warning, TEXT("Differant Actor"));
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,Hit.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlayWorldCameraShake(GetWorld() , CameraShakeAsset,Hit.ImpactPoint,500,2000);
		
		Destroy(true);
	}
}

// Called when the game starts or when spawned
void AMMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

	/*if (GetInstigator()) {
		USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(GetInstigator()->FindComponentByClass(USkeletalMeshComponent::StaticClass()));
		if (mesh) {

			FVector HandLocation= mesh->GetSocketLocation("Muzzle_01");
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnVFX, HandLocation, FRotator::ZeroRotator);
		}


	}*/

	

	//FlightSoundComponent->Play();
}

void AMMagicProjectile::PostInitializeComponents() {

	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AMMagicProjectile::OnActorOverlap);

}

void AMMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AActor* owner = GetInstigator();

	if (OtherActor&&OtherActor!= owner) {

		 UMAttributeComponent* AttributeComp= Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
		 UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
		 UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, SweepResult.ImpactPoint);


		 owner = GetInstigator();
		 
		 if (owner) {

			UMAttributeComponent* ActorAttributies = Cast<UMAttributeComponent>(owner->FindComponentByClass(UMAttributeComponent::StaticClass()));

			if (AttributeComp) {

				AttributeComp->ApplyHealthChange(-1 * ActorAttributies->GetDamage());
				Destroy(true);
			}

		 }
		 else {
			 if (AttributeComp) {

				 AttributeComp->ApplyHealthChange(-1 * DamageAmount);
				 Destroy(true);
			 }
		 }
	
	}


}


