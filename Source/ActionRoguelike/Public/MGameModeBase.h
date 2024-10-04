// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h"
#include "MGameModeBase.generated.h"

/**
 * 
 */
class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
UCLASS()
class ACTIONROGUELIKE_API AMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UEnvQuery* SpawnBotQuery;
	
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly ,Category = "AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly,Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditAnywhere, Category = "Game")
	TArray<TSubclassOf<AActor>>Powerups;

	
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	UEnvQuery* SpawnPowerupsQuary;


	FTimerHandle TimerHandle_SpawnBots;
	

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);


	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnSpawnPowerUpQuaryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	
public:

	
	UFUNCTION()
	virtual void OnActorKilled(AActor* VictimActor , AActor* Killer);

	
	UFUNCTION(Exec)
	void KillAll();

	AMGameModeBase();
	virtual void StartPlay() override;
	
};
