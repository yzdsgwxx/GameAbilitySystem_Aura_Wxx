#include "AuraCharacterBase.h"
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
		FGameplayAbilitySpec Spec(GA);
		AuraASC->GiveAbility(Spec);
	}
	for (auto GE :Effects)
	{
		auto Context = AuraASC->MakeEffectContext();
		auto Spec = AuraASC->MakeOutgoingSpec(GE,1,Context);
		AuraASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
	AuraASC->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&AAuraCharacterBase::OnAnyEffectAppliedToSelf);
}

void AAuraCharacterBase::OnAnyEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *FString(__FUNCTION__),*FString::Printf(TEXT("GEApplied")));
}
