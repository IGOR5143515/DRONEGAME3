// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UMyAIPerceptionComponent;
class  UBehaviorTree;


UCLASS()
class DRONEGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UMyAIPerceptionComponent* PerceptionComp;
	
	virtual void Tick(float DeltaTime) override;

	

public:
	virtual void OnPossess(APawn* InPawn) override;
	bool isPersonDead = false;
};
