// Fill out your copyright notice in the Description page of Project Settings.


#include "MInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "MWorldUserWidget.h"

static TAutoConsoleVariable<bool>CVarDebugDrawInteraction(TEXT("mu.InteractionDebugDraw"), false, TEXT("Enable Debug Logs to the InteractionComponent"), ECVF_Cheat);



// Sets default values for this component's properties
UMInteractionComponent::UMInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceRadius = 30.0f;
	TraceDistance = 500.0f;
	CollisionChannel = ECC_WorldDynamic;
}

void UMInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UMInteractionComponent::TickComponent(float DeltaTime,ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FindBestInteractable();
}

void UMInteractionComponent::FindBestInteractable()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	AActor* MyOwner = GetOwner();

	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);



	FVector End = EyeLocation + EyeRotation.Vector() * TraceDistance;
	

	TArray<FHitResult>Hits;


	FCollisionShape shape;
	shape.SetSphere(TraceRadius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, shape);
	FColor Color = bBlockingHit ? FColor::Green : FColor::Red;
	
	FocusedActor = nullptr;
	
	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw) {
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, Color, false, 2.00);
		}
		AActor* HitActor = Hit.GetActor();
		if (HitActor) {


			if (HitActor->Implements<UMGameplayInterface>()) {

				FocusedActor = HitActor;
				
				break;
			}


		}

	}

	if (FocusedActor) {

		if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass)) {

			DefaultWidgetInstance= CreateWidget<UMWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if (DefaultWidgetInstance) {

			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport()) {

				DefaultWidgetInstance->AddToViewport();
			}
		}

	}
	else {
		if (DefaultWidgetInstance) {
			DefaultWidgetInstance->RemoveFromParent();
		}
	}

	if (bDebugDraw) {

		DrawDebugLine(GetWorld(), EyeLocation, End, Color, false, 2.00, 0, 2.00);
	}

}



void UMInteractionComponent::PrimaryInteract() {

	
	if (FocusedActor==nullptr)
	{

		GEngine->AddOnScreenDebugMessage(-1, -1.0f, FColor::Red,"No Focused Actor to interact");
		return;
	}
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IMGameplayInterface::Execute_Interact(FocusedActor, MyPawn);
	
}