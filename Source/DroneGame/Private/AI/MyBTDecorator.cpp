// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTDecorator.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

UMyBTDecorator::UMyBTDecorator()
{

	NodeName = "Health percent";

}

bool UMyBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)return false;

	auto HealthComponent =Cast<UHealthComponent>(Controller->GetPawn()->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetPercent() < HealthPercent;
}
