// Fill out your copyright notice in the Description page of Project Settings.
#include "MBarrel.h"
#include "MAttributeComponent.h"
// Sets default values
AMBarrel::AMBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

// Called when the game starts or when spawned
void AMBarrel::BeginPlay()
{
	Super::BeginPlay();
	
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
			 AttributeComp->ApplyHealthChange(-50);
		 }
	}

}


// Called every frame
void AMBarrel::Tick(float DeltaTime)
{
	PrimaryActorTick.bCanEverTick = true;
}

