// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameModeBase.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryManager.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/MAICharacter.h"
#include "MAttributeComponent.h"
#include "EngineUtils.h"
AMGameModeBase::AMGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AMGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AMGameModeBase::SpawnBotTimerElapsed,SpawnTimerInterval,true);
}

void AMGameModeBase::SpawnBotTimerElapsed()
{
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


	int32 NumOfAliveBots = 0;
	for (TActorIterator<AMAICharacter> It(GetWorld()); It; ++It) {

		AMAICharacter* Bot = *It;

		UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(Bot->GetComponentByClass(UMAttributeComponent::StaticClass()));

		if (AttributeComp && AttributeComp->IsAlive()) {
			NumOfAliveBots++;
		}


	}

	float MaxAliveBots = 10.0f;

	if (DifficultyCurve)
	{
		MaxAliveBots = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumOfAliveBots >= MaxAliveBots) {
		return;
	}


	TArray<FVector>Locations = QueryInstance->GetResultsAsLocations();




	if (Locations.IsValidIndex(0)) {
		
		 GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

	}

}

