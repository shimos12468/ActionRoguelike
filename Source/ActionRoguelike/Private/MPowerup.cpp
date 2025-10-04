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
	RespawnTime = 10.0f;
	SetReplicates(true);
}

void AMPowerup::Deactivate()
{
	Visiable = false;
	OnRip_ShowPowerup();
	GetWorldTimerManager().SetTimer(TimerHandle_DeactivateMesh, this, &AMPowerup::Activate, RespawnTime);
}

void AMPowerup::Activate()
{
	Visiable = true;
	OnRip_ShowPowerup();
}

void AMPowerup::OnRip_ShowPowerup()
{
	SetActorEnableCollision(Visiable);
	// Set visibility on root and all children
	RootComponent->SetVisibility(Visiable, true);
	
}


void AMPowerup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPowerup, Visiable);
}
