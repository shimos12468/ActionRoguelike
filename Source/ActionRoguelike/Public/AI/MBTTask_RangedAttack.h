// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MBTTask_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere,Category = "AI")
	TSubclassOf<AActor> ProjectileClass;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
