#include "AuraAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitMaxLevel(3);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Level,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxLevel,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,PhysicsAttack,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0,GetMaxHealth());		
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0,GetMaxMana());
	}
	if (Attribute == GetLevelAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0,GetMaxLevel());
	}
}

void UAuraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetMaxHealthAttribute())
	{
		float Ratio  = OldValue==0?1:GetHealth()/OldValue;
		SetHealth(NewValue* Ratio);
	}
	if (Attribute == GetMaxManaAttribute())
	{
		float Ratio  = OldValue==0?1:GetMana()/OldValue;
		SetMana(NewValue* Ratio);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FGameplayAttribute ExecutedAttribte = Data.EvaluatedData.Attribute;
	if (ExecutedAttribte == GetHealthAttribute() || ExecutedAttribte == GetMaxHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}
	if (ExecutedAttribte == GetManaAttribute() || ExecutedAttribte == GetMaxManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0,GetMaxMana()));
	}
	if (ExecutedAttribte == GetLevelAttribute() || ExecutedAttribte == GetMaxLevelAttribute())
	{
		SetLevel(FMath::Clamp(GetLevel(),0,GetMaxLevel()));
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldAttribute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Health,OldAttribute);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldAttribute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,MaxHealth,OldAttribute);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldAttribute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Mana,OldAttribute);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldAttribute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,MaxMana,OldAttribute);
}

void UAuraAttributeSet::OnRep_Level(const FGameplayAttributeData& OldAttribute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Level,OldAttribute);
}

void UAuraAttributeSet::OnRep_MaxLevel(const FGameplayAttributeData& OldAttribute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,MaxLevel,OldAttribute);
}

void UAuraAttributeSet::OnRep_PhysicsAttack(const FGameplayAttributeData& OldAttribute)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,PhysicsAttack,OldAttribute);
}
