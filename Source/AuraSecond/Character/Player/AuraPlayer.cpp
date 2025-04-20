#include "AuraPlayer.h"
#include "AuraPlayerState.h"
#include "AuraSecond/Character/GAS/AuraAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAuraPlayer::AAuraPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 480, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	bUseControllerRotationYaw = false;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetWorldRotation(FRotator(-45,-45,0));
	SpringArm->TargetArmLength = 800;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AAuraPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SetupActorInfo();
	GiveGEAndGA();
}

void AAuraPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	SetupActorInfo();
}

void AAuraPlayer::SetupActorInfo()
{
	if (AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>())
	{
		AuraAttributeSet = AuraPS->GetAuraAttributeSet();
		AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
		if (AuraASC)
		{
			AuraASC->InitAbilityActorInfo(GetController(),this);
		}		
	}
}