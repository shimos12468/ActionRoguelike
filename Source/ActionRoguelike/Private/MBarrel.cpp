// Fill out your copyright notice in the Description page of Project Settings.


#include "MBarrel.h"
// Sets default values
AMBarrel::AMBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Explosive mesh");
	RadialForce=CreateDefaultSubobject<URadialForceComponent>("Radial Force 1");
	RadialForce->SetupAttachment(mesh);

}

// Called when the game starts or when spawned
void AMBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

