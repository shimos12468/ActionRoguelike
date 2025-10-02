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
#include "Net/UnrealNetwork.h"
#include <AI/MAIController.h>
// Sets default values
AMAICharacter::AMAICharacter()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
    AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
    ActionComp = CreateDefaultSubobject<UMActionComponent>("ActionComp");
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    ActivationDuration = 1.0f;
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
    GetMesh()->SetGenerateOverlapEvents(true);
    SetReplicates(true);
}

void AMAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
  
    PawnSensingComponent->OnSeePawn.AddDynamic(this, &AMAICharacter::OnPawnSeen);
    AttributeComp->OnHealthChanged.AddDynamic(this, &AMAICharacter::OnHealthChanged);
}
void AMAICharacter::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController());
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

           
            if (AIController) {

                AIController->GetBrainComponent()->StopLogic("Killed");
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

void AMAICharacter::MulticastPawnSeen_Implementation()
{
	if (SpottedPlayerWidget == nullptr) {

		SpottedPlayerWidget = CreateWidget<UMWorldUserWidget>(GetWorld(), playerSpottedWidgetClass);
	}
	SpottedPlayerWidget->AttachedActor = Cast<AMAICharacter>(this);
	SpottedPlayerWidget->AddToViewport(10);
	GetWorldTimerManager().SetTimer(TimerHandle_DeactivateSpottedPlayerWidget, Cast<AMAICharacter>(this), &AMAICharacter::DeactivateSpottedPlayerWidget, ActivationDuration);
}


void AMAICharacter::SetTargetActor(AActor* NewTargetActor)
{
    if (TargetActor == nullptr || TargetActor != NewTargetActor) {
        TargetActor = NewTargetActor;
    }
    AMAIController* AIC = Cast<AMAIController>(GetController());
    if (AIC && AIC->GetBlackboardComponent())
    {
        AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetActor);
    }
}

void AMAICharacter::OnPawnSeen(APawn* Pawn)
{
    

    if (GetTargetActor() != Pawn) {

        SetTargetActor(Pawn);
        MulticastPawnSeen_Implementation();
		AAIController* AIC = Cast<AAIController>(GetController());
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();
		BBComp->SetValueAsFloat("HealthLimit", 60);
    }

  
    
} 

void AMAICharacter::DeactivateSpottedPlayerWidget()
{
    SpottedPlayerWidget->AttachedActor = nullptr;
    SpottedPlayerWidget->RemoveFromViewport();
}

AActor* AMAICharacter::GetTargetActor()
{
	AAIController* AIC = Cast<AAIController>(GetController());
	
    if (AIC)
    {
        UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();
    
        return Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
    }
    
    return nullptr;

}

