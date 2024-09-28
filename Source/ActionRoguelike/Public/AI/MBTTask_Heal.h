// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MBTTask_Heal.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMBTTask_Heal : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector HealthKey;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
