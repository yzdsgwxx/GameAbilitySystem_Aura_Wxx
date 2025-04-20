#pragma once

#include "CoreMinimal.h"
#include "AuraSecond/Character/AuraCharacterBase.h"
#include "AuraSecond/Game/Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURASECOND_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
