#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class AURASECOND_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="FirstAttribute")
	FGameplayAttributeData Health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldAttribute);
	ATTRIBUTE_ACCESSORS(ThisClass,Health);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="FirstAttribute")
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldAttribute);
	ATTRIBUTE_ACCESSORS(ThisClass,MaxHealth);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="FirstAttribute")
	FGameplayAttributeData Mana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldAttribute);
	ATTRIBUTE_ACCESSORS(ThisClass,Mana);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="FirstAttribute")
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldAttribute);
	ATTRIBUTE_ACCESSORS(ThisClass,MaxMana);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Level,Category="FirstAttribute")
	FGameplayAttributeData Level;
	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& OldAttribute);
	ATTRIBUTE_ACCESSORS(ThisClass,Level);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxLevel,Category="FirstAttribute")
	FGameplayAttributeData MaxLevel;
	UFUNCTION()
	void OnRep_MaxLevel(const FGameplayAttributeData& OldAttribute);
	ATTRIBUTE_ACCESSORS(ThisClass,MaxLevel);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Level,Category="FirstAttribute")
	FGameplayAttributeData PhysicsAttack;
	UFUNCTION()
	void OnRep_PhysicsAttack(const FGameplayAttributeData& OldAttribute);
	ATTRIBUTE_ACCESSORS(ThisClass,PhysicsAttack);
};
