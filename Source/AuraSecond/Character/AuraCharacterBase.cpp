#include "AuraCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraSecond/Game/AuraGameplayTag.h"
#include "GAS/AuraAbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(),"WeaponHandSocket");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AuraASC;
}

UAuraAttributeSet* AAuraCharacterBase::GetAuraAttributeSet()const
{
	return AuraAttributeSet;
}

void AAuraCharacterBase::GiveGEAndGA()
{
	for (TSubclassOf<UGameplayAbility> GA : Abilites)
	{
		if(!GA) return;
		FGameplayAbilitySpec Spec(GA);
		AuraASC->GiveAbility(Spec);
	}
	for (TSubclassOf<UGameplayEffect> GE :Effects)
	{
		if (!GE) return;
		auto Context = AuraASC->MakeEffectContext();
		auto Spec = AuraASC->MakeOutgoingSpec(GE,1,Context);
		AuraASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
	LevelUp(StartLevel);
	AuraASC->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&AAuraCharacterBase::OnAnyEffectAppliedToSelf);
}

void AAuraCharacterBase::OnAnyEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *FString(__FUNCTION__),*FString::Printf(TEXT("GEApplied")));
}

void AAuraCharacterBase::LevelUp(int32 InLevel)
{
	if (!LevelUpGE) return;
	FGameplayEffectContextHandle Context = AuraASC->MakeEffectContext();
	auto SpecHandle = AuraASC->MakeOutgoingSpec(LevelUpGE, 1, Context);
	auto Spec = SpecHandle.Data.Get();
	Spec->SetSetByCallerMagnitude(AssignTag_Level,InLevel);
	AuraASC->ApplyGameplayEffectSpecToSelf(*Spec);
}
