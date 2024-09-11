// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MBTService_CheckAttackRange.h"
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/AIController.h>

void UMBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackBoardComp)) {

		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));

		if (TargetActor) {
			
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController)) {
				APawn* MyPawn = MyController->GetPawn();

				if (ensure(MyPawn)) {


					float DistanceTo = FVector::Distance(MyPawn->GetActorLocation(), TargetActor->GetActorLocation());
					bool bWithinRange = DistanceTo < 2000.f;

					bool bLineOfSight = false;
					if (bWithinRange) {

						bLineOfSight = MyController->LineOfSightTo(TargetActor);
					}


					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bLineOfSight&&bWithinRange));
				
				}

			}

		}
	}

}
