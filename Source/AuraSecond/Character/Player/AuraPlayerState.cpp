#include "AuraPlayerState.h"
#include "AuraSecond/Character/GAS/AuraAbilitySystemComponent.h"
#include "AuraSecond/Character/GAS/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;
	AuraASC = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AuraASC"));
	AuraASC->SetIsReplicated(true);
	AuraASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AuraAttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AuraAttributeSet"));
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AuraASC;
}

UAuraAttributeSet* AAuraPlayerState::GetAuraAttributeSet() const
{
	return AuraAttributeSet;
}
