// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraSecond/Character/AuraCharacterBase.h"
#include "AuraPlayer.generated.h"

class UGameplayAbility;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURASECOND_API AAuraPlayer : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraPlayer();
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	void SetupActorInfo();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent*Camera;
};
