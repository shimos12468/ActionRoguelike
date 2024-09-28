// Fill out your copyright notice in the Description page of Project Settings.


#include "MItemChest.h"

// Sets default values
AMItemChest::AMItemChest()
{

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	LidMesh=CreateDefaultSubobject<UStaticMeshComponent>("hey");
	LidMesh->SetupAttachment(BaseMesh);
	
	TargetPitch = 0;
}

void AMItemChest::Interact_Implementation(APawn* InstigatorPawn) {

	LidMesh->SetRelativeRotation(FRotator(0 , 0, TargetPitch));
}



