#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraAttributeSet;
class UAuraAbilitySystemComponent;
class AAuraPlayerState;
class AAuraPlayer;
class UMainOverlay;
class AAuraEnemy;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
struct FOnAttributeChangeData;

UCLASS()
class AURASECOND_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void AcknowledgePossession(class APawn* P) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	void MoveToMouse(const FInputActionValue& InputActionValue);
	void SetupMainOverlay();
	void UpdateHealth(const FOnAttributeChangeData& OnAttributeChangeData);
	void UpdateMana(const FOnAttributeChangeData& OnAttributeChangeData);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveToAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UMainOverlay> MainOverlayClass;
	
	AAuraEnemy* EnemyUnderCursor;
	AAuraPlayer* AuraPlayerRef;
	AAuraPlayerState* AuraPlayerStateRef;
	UAuraAbilitySystemComponent* AuraASCRef;
	const UAuraAttributeSet* AuraAttributSetRef;
	UMainOverlay* MainOverlayRef;
	
};
