// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "MAction.generated.h"
class UWorld;
class UMActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API UMAction : public UObject
{
	GENERATED_BODY()
	
protected:


	UFUNCTION(BlueprintCallable ,Category = "Action")
	UMActionComponent* GetOwningComponent()const;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer GrantsTags;
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer BlockedTags;

	bool bIsRunning = false;


public:
	UPROPERTY(EditDefaultsOnly,Category = "Action")
	bool bIsAutoStart;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning()const;


	UFUNCTION(BlueprintCallable, Category = "Action")
	FName GetActionName();

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);


	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	
	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;
	
	UWorld* GetWorld() const override;
};
