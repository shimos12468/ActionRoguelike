// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MActionComponent.generated.h"


class UMAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UMActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;


	UFUNCTION(BlueprintCallable,Category = "Action")
	void AddAction(AActor* Instigator,TSubclassOf<UMAction> ActionClass);


	UFUNCTION(BlueprintCallable, Category = "Action")
	void RemoveAction(UMAction* Action);


	UFUNCTION(Server,Reliable)
	void ServerStartAction(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator,FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Action")
	TArray<UMAction*> GetActionsList();

	UFUNCTION(BlueprintCallable, Category = "Action")
	UMAction* GetAction(TSubclassOf<UMAction>ActionClass) const ;


	UMActionComponent();


protected:

	UPROPERTY(EditAnywhere,Category = "Actions")
	TArray<TSubclassOf<UMAction>>DefaultActions;

	UPROPERTY(Replicated)
	TArray<UMAction*>Actions;
	
	virtual void BeginPlay() override;


	bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
