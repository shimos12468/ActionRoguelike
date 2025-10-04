// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "MPlayerState.generated.h"




class UMSaveGame;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, AMPlayerState*, PlayerState, int32, NewCredits, int32, Delta);
UCLASS()
class ACTIONROGUELIKE_API AMPlayerState : public APlayerState
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditDefaultsOnly,ReplicatedUsing="OnRep_Credits" , Category = "Attributes")
	int PlayerCredits;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	int GetCredit();
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddCredit(int Amount);
	UFUNCTION(BlueprintCallable ,Category = "Attribute")
	void RemoveCredit(int Amount);
	UFUNCTION()
	void OnRep_Credits(int NewCredits);

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(UMSaveGame* CurrentSaveGame);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(UMSaveGame* CurrentSaveGame);


	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;

};
