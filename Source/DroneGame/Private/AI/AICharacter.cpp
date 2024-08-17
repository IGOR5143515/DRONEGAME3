// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "MyAIController.h"
#include "Components/ShootingComponent.h"

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	auto AIController = Cast<AMyAIController>(GetController());
	if (!AIController)return;


	AIController->isPersonDead = true;

	const auto BotController = Cast<AAIController>(Controller);
	if (BotController && BotController->BrainComponent) {

		BotController->BrainComponent->Cleanup();
		BotController->BrainComponent->Deactivate();
		}

	
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	auto ShootComp =Cast <UShootingComponent>(GetComponentByClass(UShootingComponent::StaticClass()));
	if (!ShootComp)return;

	ShootComp->MaxBullets = 10000;
	ShootComp->SetBullets(10000);


}


