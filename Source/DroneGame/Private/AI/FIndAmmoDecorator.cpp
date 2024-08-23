// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FIndAmmoDecorator.h"
#include "Components/ShootingComponent.h"
#include "AIController.h"

UFIndAmmoDecorator::UFIndAmmoDecorator()
{
	NodeName = "Find Ammo";
}

bool UFIndAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UE_LOG(LogTemp, Error, TEXT("Find Ammo!"));

	auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)return false;

	auto ShootComponent = Cast<UShootingComponent>(AIController->GetPawn()->GetComponentByClass(UShootingComponent::StaticClass()));
	if (!ShootComponent||ShootComponent->GetBullets()== ShootComponent->GetMaxBullets())return false;

	return ShootComponent->GetPertcent() <= AmmoPercent;


}
