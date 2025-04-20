#include "AuraEnemy.h"

#include "AbilitySystemComponent.h"
#include "AuraSecond/Character/GAS/AuraAbilitySystemComponent.h"
#include "AuraSecond/Character/GAS/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
	AuraASC = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AuraASC"));
	AuraASC->SetIsReplicated(true);
	AuraASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AuraAttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AuraAttributeSet"));
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	AuraASC->InitAbilityActorInfo(this,this);
	GiveGEAndGA();
}

void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAuraEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

