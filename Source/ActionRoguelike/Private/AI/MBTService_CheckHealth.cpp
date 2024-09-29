// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MBTService_CheckHealth.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/AIController.h"
#include "MAttributeComponent.h"

void UMBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackBoardComp)) {

		AAIController* MyController = OwnerComp.GetAIOwner();

		if (MyController) {

			APawn* MyPawn = MyController->GetPawn();
			if (ensure(MyPawn)) {
				UMAttributeComponent* AttrebuteComp = Cast<UMAttributeComponent>(MyPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));

				if (ensure(AttrebuteComp)) {
					float CurrentHealth = AttrebuteComp->GetHealth();
					float Limit = BlackBoardComp->GetValueAsFloat(HealthLimit.SelectedKeyName);

					BlackBoardComp->SetValueAsBool(HealthKey.SelectedKeyName, CurrentHealth<Limit);

				}

			}

		}


	}

}
