#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericGlobe.generated.h"

class UProgressBar;

UCLASS()
class AURASECOND_API UGenericGlobe : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateBar(float cur, float max);
	
	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UProgressBar* ProgressBar;
};
