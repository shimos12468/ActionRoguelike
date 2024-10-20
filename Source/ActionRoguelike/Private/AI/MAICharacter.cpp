// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MAICharacter.h"
#include <Perception/PawnSensingComponent.h>
#include "AIController.h"
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <DrawDebugHelpers.h>
#include "MAttributeComponent.h"
#include "BrainComponent.h"
#include "MWorldUserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MActionComponent.h"
// Sets default values
AMAICharacter::AMAICharacter()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
    AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
    ActionComp = CreateDefaultSubobject<UMActionComponent>("ActionComp");
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
    GetMesh()->SetGenerateOverlapEvents(true);
}

void AMAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    PawnSensingComponent->OnSeePawn.AddDynamic(this, &AMAICharacter::OnPawnSeen);
    AttributeComp->OnHealthChanged.AddDynamic(this, &AMAICharacter::OnHealthChanged);
}

void AMAICharacter::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f) {

        if (InstigatorActor != this) {

            SetTargetActor(InstigatorActor);
        }



        if (ActiveWidget == nullptr) {

            ActiveWidget = CreateWidget<UMWorldUserWidget>(GetWorld(), HealthBarWidgetClass);

            if (ActiveWidget) {
                ActiveWidget->AttachedActor = this;
                ActiveWidget->AddToViewport();
            }

        }

        GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);


        if (NewHealth <= 0.0f) {

            AAIController* AIC = Cast<AAIController>(GetController());
            if (AIC) {

                AIC->GetBrainComponent()->StopLogic("Killed");
            }

            // original way for death animation

            GetMesh()->SetAllBodiesSimulatePhysics(true);
            GetMesh()->SetCollisionProfileName("Ragdoll");
            GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            GetCharacterMovement()->DisableMovement();
            SetLifeSpan(10.0f);
        }

    }


    
}


void AMAICharacter::SetTargetActor(AActor* TargetActor)
{
	AAIController* AIC = Cast<AAIController>(GetController());

    AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetActor);

}

void AMAICharacter::OnPawnSeen(APawn* Pawn)
{

    SetTargetActor(Pawn);

    AAIController* AIC = Cast<AAIController>(GetController());
    UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();
    BBComp->SetValueAsFloat("HealthLimit", 60);
    DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::Red, 4.0f, true);
    
}



