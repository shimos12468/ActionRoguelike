// Fill out your copyright notice in the Description page of Project Settings.


#include "MItemChest.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMItemChest::AMItemChest()
{

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	LidMesh=CreateDefaultSubobject<UStaticMeshComponent>("hey");
	LidMesh->SetupAttachment(BaseMesh);
	
	TargetPitch = 0;
	SetReplicates(true);
}



void AMItemChest::Interact_Implementation(APawn* InstigatorPawn) {
	
	bLidOpened = !bLidOpened;

	OnRip_LidOpened();
}

void AMItemChest::OnRip_LidOpened()
{

	float CurrentPitch = bLidOpened ? TargetPitch : 0;
	LidMesh->SetRelativeRotation(FRotator(0, 0, CurrentPitch));
}
void AMItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMItemChest, bLidOpened);
}



