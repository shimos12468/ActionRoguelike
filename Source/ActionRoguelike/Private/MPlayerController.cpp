// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerController.h"

void AMPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	OnPawnChanged.Broadcast(InPawn);
}
