// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericGlobe.h"

#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UGenericGlobe::UpdateBar(float cur, float max)
{
	//TODO 渐变效果
	ProgressBar->SetPercent(UKismetMathLibrary::SafeDivide(cur, max));
}
