// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UMyAIPerceptionComponent;

UCLASS()
class DRONEGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UMyAIPerceptionComponent* PerceptionComp;
	
	virtual void Tick(float DeltaTime) override;
	
	bool isPersonDead = false;
};
