// Fill out your copyright notice in the Description page of Project Settings.


#include "GAGEGiven.h"

#include "AbilitySystemComponent.h"

void UGAGEGiven::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if (bAutoActivate)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}
