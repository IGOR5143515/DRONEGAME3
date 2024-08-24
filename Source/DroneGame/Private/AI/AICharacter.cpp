// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "MyAIController.h"
#include "Components/ShootingComponent.h"
#include "Components/MyAIPerceptionComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

AAICharacter::AAICharacter():Super()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AMyAIController::StaticClass();


}


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

	auto PerceptionComp = Cast<UMyAIPerceptionComponent>(AIController->GetComponentByClass(UMyAIPerceptionComponent::StaticClass()));
	if (!PerceptionComp) return;
	
	TSubclassOf<UAISense> SightSenseClass = UAISense_Sight::StaticClass();

	PerceptionComp->SetSenseEnabled(SightSenseClass, false);


	
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	auto ShootComp =Cast <UShootingComponent>(GetComponentByClass(UShootingComponent::StaticClass()));
	if (!ShootComp)return;


	ShootComp->Damage = 1.0f;


}



