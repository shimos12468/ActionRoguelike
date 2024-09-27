// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MAICharacter.h"
#include <Perception/PawnSensingComponent.h>
#include "AIController.h"
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <DrawDebugHelpers.h>
#include "MAttributeComponent.h"

// Sets default values
AMAICharacter::AMAICharacter()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
    AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    PawnSensingComponent->OnSeePawn.AddDynamic(this, &AMAICharacter::OnPawnSeen);
}

void AMAICharacter::OnPawnSeen(APawn* Pawn)
{
    AAIController* AIC = Cast<AAIController>(GetController());
    
    if (AIC) {

        UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

        BBComp->SetValueAsObject("TargetActor", Pawn);
        DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::Red, 4.0f, true);
    }
}

