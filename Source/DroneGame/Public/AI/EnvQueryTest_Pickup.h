// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API UEnvQueryTest_Pickup : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	UEnvQueryTest_Pickup(const FObjectInitializer &ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
