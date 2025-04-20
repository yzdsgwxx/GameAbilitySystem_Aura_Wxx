#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UAuraAttributeSet;
class UAttributeSet;
class UAuraAbilitySystemComponent;

UCLASS(Abstract)
class AURASECOND_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraCharacterBase();

	/*
	 * IAbilitySystemInterface
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAuraAttributeSet* GetAuraAttributeSet()const;
	void GiveGEAndGA();
	void OnAnyEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	UAuraAbilitySystemComponent* AuraASC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	UAuraAttributeSet* AuraAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	TArray<TSubclassOf<UGameplayAbility>> Abilites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	TArray<TSubclassOf<UGameplayEffect>> Effects;
};
