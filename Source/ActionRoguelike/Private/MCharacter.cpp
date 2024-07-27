// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MInteractionComponent.h"
#include <Kismet/KismetMathLibrary.h>
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

	GetCharacterMovement()-> bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMCharacter::PrimaryInteract);
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

void AMCharacter::PrimaryAttack() {

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttrack, this, &AMCharacter::PrimaryAttack_TimeElapsed, 0.2f);

}

void AMCharacter::PrimaryAttack_TimeElapsed() {

	

	FVector Start = CameraComp->GetComponentLocation();
	FVector End = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

	FCollisionShape Shape;
	Shape.SetSphere(20);

	FHitResult Hit;

	FCollisionObjectQueryParams CollisionParams;

	CollisionParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	CollisionParams.AddObjectTypesToQuery(ECC_Pawn);
	CollisionParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	

	bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit, Start, End, FQuat::Identity, CollisionParams, Shape,Params);

	if (bBlockingHit) {

		End = Hit.ImpactPoint;
	}

	//DrawDebugLine(GetWorld(), CameraComp->GetComponentLocation(), CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000),FColor::Red,true,2.00f,3.00f);

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//the first way
	
	//FRotator Rotation= UKismetMathLibrary::FindLookAtRotation(HandLocation, End);
	
	//the second way
	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(End - HandLocation);
	
	FTransform SpawnTM = FTransform(Rotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	SpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}


void AMCharacter::PrimaryInteract() {

	if (InteractionComp) {

		InteractionComp->PrimaryInteract();
	}

}