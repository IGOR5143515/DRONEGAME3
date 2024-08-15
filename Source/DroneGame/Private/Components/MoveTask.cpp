// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MoveTask.h"

EBTNodeResult::Type UMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Error, TEXT("Task"));

	return EBTNodeResult::Succeeded;
}
