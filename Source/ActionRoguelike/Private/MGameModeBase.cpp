// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameModeBase.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryManager.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/MAICharacter.h"
#include "MAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "MCharacter.h"
#include "MPlayerState.h"

static TAutoConsoleVariable<bool>CVarSpawnBots(TEXT("mu.SpawnBots"), true, TEXT("Enable/Disable Spawning bots via timer"), ECVF_Cheat);

AMGameModeBase::AMGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AMGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AMGameModeBase::SpawnBotTimerElapsed,SpawnTimerInterval,true);


	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnPowerupsQuary, this, EEnvQueryRunMode::AllMatching, nullptr);

	if (ensure(QueryInstance)) {
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AMGameModeBase::OnSpawnPowerUpQuaryCompleted);
	}


}


void AMGameModeBase::OnSpawnPowerUpQuaryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	UE_LOG(LogTemp, Warning, TEXT("RPWEUIRPWOEURJPW"));
	TArray<FVector> Locations;
	QueryInstance->GetQueryResultsAsLocations(Locations);
	for (int i = 0; i < Locations.Num(); i++) {


		int number= FMath::RandRange(0, Powerups.Num()-1);

		GetWorld()->SpawnActor<AActor>(Powerups[number], Locations[i], FRotator::ZeroRotator);
	}

}



void AMGameModeBase::SpawnBotTimerElapsed()
{

	if (!CVarSpawnBots.GetValueOnGameThread()) {
		return;
	}


	int32 NumOfAliveBots = 0;
	for (TActorIterator<AMAICharacter> It(GetWorld()); It; ++It) {

		AMAICharacter* Bot = *It;

		UMAttributeComponent* AttributeComp =UMAttributeComponent::GetAttributies(Bot);

		if (ensure(AttributeComp) && AttributeComp->IsAlive()) {
			NumOfAliveBots++;
		}


	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots !"), NumOfAliveBots);

	float MaxAliveBots = 10.0f;

	if (DifficultyCurve)
	{
		MaxAliveBots = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumOfAliveBots >= MaxAliveBots) {

		UE_LOG(LogTemp, Log, TEXT("At maximum Bot capaicty ,skipping Bot Spawn"));
		return;
	}


	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance)) {

		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AMGameModeBase::OnQueryCompleted);
	}
}

void AMGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success) {
		
		UE_LOG(LogTemp,Warning , TEXT("Spawn bot Query Failed!!"))
		return;
	}

	TArray<FVector>Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0)) {
		
		 GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
		 DrawDebugSphere(GetWorld(), Locations[0], 50, 20, FColor::Blue, false, 60);
	}

}

void AMGameModeBase::KillAll()
{
	for (TActorIterator<AMAICharacter> It(GetWorld()); It; ++It) {

		AMAICharacter* Bot = *It;

		UMAttributeComponent* AttributeComp = UMAttributeComponent::GetAttributies(Bot);

		if (ensure(AttributeComp) && AttributeComp->IsAlive()) {
			AttributeComp->Kill(this);
		}


	}
}


void AMGameModeBase::RespawnPlayerElapsed(AController* Controller)
{

	if (ensure(Controller)) {

		Controller->UnPossess();

		
		RestartPlayer(Controller);
		
	}


}

void AMGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	AMCharacter* Player = Cast<AMCharacter>(VictimActor);

	if (Player) {

		FTimerHandle TimeHandle_RespawnDelay;

		FTimerDelegate Delegate;

		float RespawnDelay = 2.f;

		Delegate.BindUFunction(this, "RespawnPlayerElapsed",Player->GetController());
		GetWorldTimerManager().SetTimer(TimeHandle_RespawnDelay,Delegate,RespawnDelay, false);

	}

	AMAICharacter* AI= Cast<AMAICharacter>(VictimActor);

	APawn* killerPawn = Cast<APawn>(Killer);
	if (AI) {

		AMPlayerState* PS = killerPawn->GetPlayerState<AMPlayerState>();

		UMAttributeComponent* VictimAttributeComp = UMAttributeComponent::GetAttributies(VictimActor);

		if (ensure(PS)) {

			
			PS->AddCredit(VictimActor, VictimAttributeComp->KilledCreditAmount);
		}

	}


}

