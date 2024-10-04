// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MBTTask_Heal.h"
#include "AIModule/Classes/AIController.h"
#include "MAttributeComponent.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "MCharacter.h"
#include "MPlayerState.h"

EBTNodeResult::Type UMBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if(!Controller)
		return EBTNodeResult::Failed;

	APawn* MyPawn = Controller->GetPawn();
	if(!MyPawn)
		return EBTNodeResult::Failed;
	
	UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(MyPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));
	if (!AttributeComp) 
		return EBTNodeResult::Failed;


	float CorrectDelta = AttributeComp->GetMaxHealth() - AttributeComp->GetHealth();
	AttributeComp->ApplyHealthChange(MyPawn ,CorrectDelta);
	


	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	BlackBoardComp->SetValueAsBool(HealthKey.SelectedKeyName, false);
	
	
	AMCharacter* Target= Cast<AMCharacter>(BlackBoardComp->GetValueAsObject("TargetActor"));
	if (Target) {

		AMPlayerState* PS = Target->GetPlayerState<AMPlayerState>();
		if (PS) {

			PS->AddCredit(MyPawn, 20);
		}
		
	}


	return EBTNodeResult::Succeeded;

}
