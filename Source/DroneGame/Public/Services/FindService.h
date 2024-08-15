// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindService.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API UFindService : public UBTService
{
	GENERATED_BODY()
public:
	UFindService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Service")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
