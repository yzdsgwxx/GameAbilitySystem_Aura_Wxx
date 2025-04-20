#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainOverlay.generated.h"


class UGenericGlobe;

UCLASS()
class AURASECOND_API UMainOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UGenericGlobe* HealthGlobe;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UGenericGlobe* ManaGlobe;
};
