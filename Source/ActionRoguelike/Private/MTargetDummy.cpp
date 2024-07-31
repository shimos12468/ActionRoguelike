// Fill out your copyright notice in the Description page of Project Settings.


#include "MTargetDummy.h"
#include <Components/StaticMeshComponent.h>
#include "MAttributeComponent.h"

// Sets default values
AMTargetDummy::AMTargetDummy()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    RootComponent = MeshComp;

    AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
    AttributeComp->OnHealthChanged.AddDynamic(this, &AMTargetDummy::OnHealthChanged);

}

void AMTargetDummy::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta)
{

    if (Delta < 0.0f) {

    
        MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    
    }

}
