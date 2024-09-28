// Fill out your copyright notice in the Description page of Project Settings.
#include "MBarrel.h"
#include "MAttributeComponent.h"
// Sets default values
AMBarrel::AMBarrel()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Explosive mesh");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	RadialForceComp=CreateDefaultSubobject<URadialForceComponent>("Radial Force 1");
	RadialForceComp->SetupAttachment(MeshComp);

	RadialForceComp->SetAutoActivate(false);
	
	RadialForceComp->Radius = 750;

	RadialForceComp->ImpulseStrength = 2500;

	RadialForceComp->bImpulseVelChange = true;


	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	
	
}



void AMBarrel::PostInitializeComponents() {
	
	Super::PostInitializeComponents();

	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AMBarrel::OnHit);

}

void AMBarrel::Explode() {
	UE_LOG(LogTemp, Warning, TEXT("DID HIT"));
	RadialForceComp->FireImpulse();



}

void AMBarrel::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	Explode();

	if (OtherActor) {
		
		 UMAttributeComponent* AttributeComp= Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
		 if (AttributeComp)
		 {
			 AttributeComp->ApplyHealthChange(this ,-50);
		 }
	}

}
