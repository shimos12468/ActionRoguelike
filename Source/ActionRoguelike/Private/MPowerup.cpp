// Fill out your copyright notice in the Description page of Project Settings.


#include "MPowerup.h"

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
}

void AMPowerup::Deactivate()
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivated"));
	BaseMesh->SetVisibility(false);
	LidMesh->SetVisibility(false);
}

void AMPowerup::Activate()
{
	UE_LOG(LogTemp, Warning, TEXT("Activated"));
	BaseMesh->SetVisibility(true);
	LidMesh->SetVisibility(true);
}
