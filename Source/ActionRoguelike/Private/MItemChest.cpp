// Fill out your copyright notice in the Description page of Project Settings.


#include "MItemChest.h"

// Sets default values
AMItemChest::AMItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	LidMesh=CreateDefaultSubobject<UStaticMeshComponent>("hey");
	LidMesh->SetupAttachment(BaseMesh);
	
	TargetPitch = 0;
}

void AMItemChest::Interact_Implementation(APawn* InstigatorPawn) {

	LidMesh->SetRelativeRotation(FRotator(0 , 0, TargetPitch));
}


// Called when the game starts or when spawned
void AMItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


