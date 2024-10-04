// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MPlayerState.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, AActor*, InstigatorActor, AActor*, OwningPlayer, float, NewCredits);
UCLASS()
class ACTIONROGUELIKE_API AMPlayerState : public APlayerState
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere ,BlueprintReadWrite , Category = "Attributes")
	int PlayerCredits;


public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	int GetCredit();
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddCredit(AActor* CreditSource, int Amount);
	UFUNCTION(BlueprintCallable ,Category = "Attribute")
	void RemoveCredit(AActor* CreditSource, int Amount);
	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;

};
