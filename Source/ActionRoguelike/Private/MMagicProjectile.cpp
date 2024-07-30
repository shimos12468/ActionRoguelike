// Fill out your copyright notice in the Description page of Project Settings.


#include "MMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MAttributeComponent.h"
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
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
		Destroy(true);
	}
}

// Called when the game starts or when spawned
void AMMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void AMMagicProjectile::PostInitializeComponents() {

	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AMMagicProjectile::OnActorOverlap);

}

void AMMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor) {

		 UMAttributeComponent* AttributeComp= Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
		
		 if (AttributeComp) {

			 AttributeComp->ApplyHealthChange(-20);
			 Destroy(true);
		 }
	
	}


}


