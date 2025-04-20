#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"


class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

UCLASS()
class AURASECOND_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	/*
	 * IAbilitySystemInterface
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributeSet* GetAuraAttributeSet()const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	UAuraAbilitySystemComponent* AuraASC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	UAuraAttributeSet* AuraAttributeSet;
};
