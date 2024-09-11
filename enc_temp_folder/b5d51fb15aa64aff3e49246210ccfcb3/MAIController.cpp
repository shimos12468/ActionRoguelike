// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackBoardComponent.h"


void AMAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	 APawn* PlayerPawn= UGameplayStatics::GetPlayerPawn(this, 0);

	 if (PlayerPawn) {
		 GetBlackboardComponent()->SetValueAsVector("MoveToLocation", PlayerPawn->GetActorLocation());

		 GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
	 }

}
