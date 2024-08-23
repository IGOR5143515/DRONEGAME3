// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FIndAmmoDecorator.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API UFIndAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	

public:

	UFIndAmmoDecorator();

protected:
	 virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	 float AmmoPercent = 0.4f;

};
