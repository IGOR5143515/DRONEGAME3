// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Components/MyAIPerceptionComponent.h"
#include "Components/HealthComponent.h"

AMyAIController::AMyAIController()
{

	PerceptionComp = CreateDefaultSubobject<UMyAIPerceptionComponent>("PerceptionComp");
	SetPerceptionComponent(*PerceptionComp);
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AimActor = PerceptionComp->GetClosesEnemy();
	SetFocus(AimActor);
	IsBotDead();
}

void AMyAIController::IsBotDead()
{

	

	//auto HealthComponent =character->GetComponentByClass(UHealthComponent::StaticClass());

	

}
