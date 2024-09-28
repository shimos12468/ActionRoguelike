// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MBTService_CheckHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMBTService_CheckHealth : public UBTService
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector HealthKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector HealthLimit;


	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
