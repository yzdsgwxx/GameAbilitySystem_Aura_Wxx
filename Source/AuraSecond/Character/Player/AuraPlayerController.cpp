#include "AuraPlayerController.h"
#include "AuraPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AuraSecond/Character/GAS/AuraAbilitySystemComponent.h"
#include "AuraSecond/Character/GAS/AuraAttributeSet.h"
#include "AuraSecond/Game/Interface/EnemyInterface.h"
#include "AuraSecond/Character/Player/AuraPlayerState.h"
#include "AuraSecond/UI/GenericGlobe.h"
#include "AuraSecond/UI/MainOverlay.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInput = GetLocalPlayer()->GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>())
	{
		EnhancedInput->AddMappingContext(InputContext,0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveToAction,ETriggerEvent::Started,this,&AAuraPlayerController::MoveToMouse);
	}
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	EnemyUnderCursor = nullptr;
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility),false,HitResult);
	if (HitResult.bBlockingHit&&Cast<IEnemyInterface>(HitResult.GetActor()))
	{
		// EnemyUnderCursor = Cast<AAuraEnemy>(HitResult.GetActor());
	}
}

void AAuraPlayerController::MoveToMouse(const FInputActionValue& InputActionValue)
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility),false,HitResult);
	if (HitResult.bBlockingHit)
	{
		FVector MoveToLocation = HitResult.Location;
		//TODO 移动角色向目的地。
	}
}

void AAuraPlayerController::SetupMainOverlay()
{
	AuraPlayerRef = GetPawn<AAuraPlayer>();
	
	 if (MainOverlayRef) return;
	 AuraPlayerStateRef = GetPlayerState<AAuraPlayerState>();
	 AuraASCRef = Cast<UAuraAbilitySystemComponent>(AuraPlayerRef->GetAbilitySystemComponent());
	 MainOverlayRef = CreateWidget<UMainOverlay>(this,MainOverlayClass);
	 if (MainOverlayRef == nullptr) return;
	
	 MainOverlayRef->AddToViewport();
	
	 if (AuraASCRef)
	 {
	 	AuraAttributSetRef = Cast<UAuraAttributeSet>(AuraASCRef->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	 	if (AuraAttributSetRef)
	 	{
	 		AuraASCRef->GetGameplayAttributeValueChangeDelegate(AuraAttributSetRef->GetHealthAttribute()).AddUObject(this,&AAuraPlayerController::UpdateHealth);
	 		AuraASCRef->GetGameplayAttributeValueChangeDelegate(AuraAttributSetRef->GetMaxHealthAttribute()).AddUObject(this,&AAuraPlayerController::UpdateHealth);
	 		AuraASCRef->GetGameplayAttributeValueChangeDelegate(AuraAttributSetRef->GetManaAttribute()).AddUObject(this,&AAuraPlayerController::UpdateMana);
	 		AuraASCRef->GetGameplayAttributeValueChangeDelegate(AuraAttributSetRef->GetMaxManaAttribute()).AddUObject(this,&AAuraPlayerController::UpdateMana);
	
	 		UpdateHealth(FOnAttributeChangeData());
	 		UpdateMana(FOnAttributeChangeData());
	 	}
	 }
}

void AAuraPlayerController::UpdateHealth(const FOnAttributeChangeData& OnAttributeChangeData)
{
	MainOverlayRef->HealthGlobe->UpdateBar(AuraAttributSetRef->GetHealth(),AuraAttributSetRef->GetMaxHealth());
}

void AAuraPlayerController::UpdateMana(const FOnAttributeChangeData& OnAttributeChangeData)
{
	MainOverlayRef->ManaGlobe->UpdateBar(AuraAttributSetRef->GetMana(),AuraAttributSetRef->GetMaxMana());
}

void AAuraPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetupMainOverlay();
}

void AAuraPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
	SetupMainOverlay();
}
