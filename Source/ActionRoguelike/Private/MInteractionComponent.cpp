// Fill out your copyright notice in the Description page of Project Settings.


#include "MInteractionComponent.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool>CVarDebugDrawInteraction(TEXT("mu.InteractionDebugDraw"), true, TEXT("Enable Debug Logs to the InteractionComponent"), ECVF_Cheat);


// Sets default values for this component's properties
UMInteractionComponent::UMInteractionComponent()
{
	
}


void UMInteractionComponent::PrimaryInteract() {

	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	AActor* MyOwner = GetOwner();
	
	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	

	
	FVector End = EyeLocation+EyeRotation.Vector()*1000;
	//FHitResult Hit;
	//GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	
	TArray<FHitResult>Hits;
	
	float Radius = 30.0;
	FCollisionShape shape;
	shape.SetSphere(Radius);
	bool bBlockingHit= GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, shape);
	FColor Color = bBlockingHit ? FColor::Green : FColor::Red;
	for (FHitResult Hit:Hits)
	{
		if (bDebugDraw) {
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, Color, false, 2.00);
		}
		AActor* HitActor = Hit.GetActor();
		if (HitActor) {

			
			if (HitActor->Implements<UMGameplayInterface>()) {

				APawn* MyPawn = Cast<APawn>(MyOwner);
				IMGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}


		}

	}

	
	if (bDebugDraw) {

		DrawDebugLine(GetWorld(), EyeLocation, End, Color, false, 2.00,0,2.00);
	}


}