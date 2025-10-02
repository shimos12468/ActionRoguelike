// Fill out your copyright notice in the Description page of Project Settings.


#include "MPowerup.h"


#include "Net/UnrealNetwork.h"
// Sets default values
AMPowerup::AMPowerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
	DeactivationDuration = 10.0f;
	SetReplicates(true);
}

void AMPowerup::Deactivate()
{
	Visiable = false;
	OnRip_CoinConsumed();

}

void AMPowerup::Activate()
{
	Visiable = true;
	OnRip_CoinConsumed();
}

void AMPowerup::OnRip_CoinConsumed()
{
	if (Visiable) {
		UE_LOG(LogTemp, Warning, TEXT("ACTIVATED"));
		BaseMesh->SetVisibility(true);
		BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		LidMesh->SetVisibility(true);
		LidMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("DEACTIVATED"));
		BaseMesh->SetVisibility(false);
		BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LidMesh->SetVisibility(false);
		LidMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AMPowerup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPowerup, Visiable);
}
