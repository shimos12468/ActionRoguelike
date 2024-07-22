// Fill out your copyright notice in the Description page of Project Settings.
#include "MBarrel.h"
// Sets default values
AMBarrel::AMBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Explosive mesh");
	MeshComp->SetCollisionProfileName("PhysicsActor");
	MeshComp->bUseDefaultCollision = true;
	RadialForceComp=CreateDefaultSubobject<URadialForceComponent>("Radial Force 1");
	RadialForceComp->SetupAttachment(MeshComp);

	RadialForceComp->ImpulseStrength = 2500;

	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	MeshComp->OnComponentHit.AddDynamic(this, &AMBarrel::OnHit);
	RootComponent = MeshComp;
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

void AMBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	Explode();
}


// Called every frame
void AMBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

