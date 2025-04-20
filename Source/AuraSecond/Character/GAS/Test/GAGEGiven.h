// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAGEGiven.generated.h"

/**
 * 
 */
UCLASS()
class AURASECOND_API UGAGEGiven : public UGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="")
	bool bAutoActivate = true;
};

