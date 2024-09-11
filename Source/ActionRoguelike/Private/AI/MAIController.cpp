// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackBoardComponent.h"


void AMAIController::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (ensureMsgf(BehaviorTree, TEXT("BehaviorTree is nullptr! Please assign BehaviorTree in your AI controller"))) {

		RunBehaviorTree(BehaviorTree);
	}
}
