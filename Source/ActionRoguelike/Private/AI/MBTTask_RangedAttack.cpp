// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MBTTask_RangedAttack.h"
#include <AIModule/Classes/AIController.h>
#include <GameFramework/Character.h>
#include "BehaviorTree/BlackBoardComponent.h"

EBTNodeResult::Type UMBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (ensure(MyController)) {

		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());

		if (MyPawn == nullptr) {

			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

		if (TargetActor == nullptr) {
		
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = MyPawn;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* NewProjectile= GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation,MuzzleRotation, SpawnParams);

		return NewProjectile? EBTNodeResult::Succeeded: EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
