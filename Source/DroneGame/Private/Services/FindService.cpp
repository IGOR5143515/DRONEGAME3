// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/FindService.h"
#include"AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/MyAIPerceptionComponent.h"

UFindService::UFindService()
{
	NodeName = "Find Enemy";
}

void UFindService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	if (BlackBoard) {
		const auto Controller = OwnerComp.GetAIOwner();

		const auto  PerceptionComponent =  Cast<UMyAIPerceptionComponent>(Controller->GetComponentByClass(UMyAIPerceptionComponent::StaticClass()));
		

		if (PerceptionComponent) {
			
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosesEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
