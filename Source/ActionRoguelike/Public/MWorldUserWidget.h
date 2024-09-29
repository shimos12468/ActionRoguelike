// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MWorldUserWidget.generated.h"

/**
 * 
 */
class USizeBox;
UCLASS()
class ACTIONROGUELIKE_API UMWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:

	UPROPERTY(EditAnywhere,Category ="UI")
	float WorldOffset;
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

	UPROPERTY(BlueprintReadOnly,Category="UI")
	AActor* AttachedActor;



	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

};
