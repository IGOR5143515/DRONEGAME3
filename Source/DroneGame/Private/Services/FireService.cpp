// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/FireService.h"
#include"AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ShootingComponent.h"

UFireService::UFireService()
{
	NodeName = "Fire";

}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();



	const auto HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	
	if (Controller) {
		const auto WeaponComponent = Cast<UShootingComponent>(Controller->GetPawn()->GetComponentByClass(UShootingComponent::StaticClass()));


		if (WeaponComponent) {
		
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
			
		}
	}

	Super::TickNode(OwnerComp, NodeMemory,DeltaSeconds);
}
