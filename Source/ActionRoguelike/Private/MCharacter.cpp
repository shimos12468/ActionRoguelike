// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MInteractionComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "MAttributeComponent.h"
#include "MPlayerState.h"
#include "MActionComponent.h"
// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	InteractionComp = CreateDefaultSubobject<UMInteractionComponent>("InteractionComp");


	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	
	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<UMActionComponent>("ActionComp");

	GetCharacterMovement()-> bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}
void AMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AMCharacter::OnHealthChanged);
}


void AMCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

FVector AMCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

void AMCharacter::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float NewHealth, float Delta)
{


	if (Delta < 0.0f) {

		USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		mesh->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

	if (Delta < 0.0f && NewHealth <= 0.0f) {
		APlayerController* pc = Cast<APlayerController>(GetController());
		DisableInput(pc);
	}

}


// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed, this,&AMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AMCharacter::BlackHole);

	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &AMCharacter::Dash);
	
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMCharacter::SprintStop);

}

void AMCharacter::HealSelf(float Amount /*= 100*/)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

void AMCharacter::MoveForward(float Value) {

	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	AddMovementInput(controlRot.Vector(), Value);
}
void AMCharacter::MoveRight(float Value) {


	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	// X = forward
	// Y = right
	// Z = up

	FVector RightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void AMCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void AMCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

void AMCharacter::PrimaryAttack() {

	ActionComp->StartActionByName(this, "PrimaryAttack");

}


void AMCharacter::BlackHole() {

	ActionComp->StartActionByName(this, "BlackHole");

}


void AMCharacter::Dash() {

	ActionComp->StartActionByName(this, "Dash");

}





void AMCharacter::PrimaryInteract() {

	if (InteractionComp) {

		InteractionComp->PrimaryInteract();
	}

}



