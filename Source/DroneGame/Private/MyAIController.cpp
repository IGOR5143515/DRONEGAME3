// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Components/MyAIPerceptionComponent.h"
#include "Components/HealthComponent.h"
#include "AI/AICharacter.h"
#include "Components/HealthComponent.h"
#include "DroneCharacter.h"

AMyAIController::AMyAIController()
{

	PerceptionComp = CreateDefaultSubobject<UMyAIPerceptionComponent>("PerceptionComp");
	SetPerceptionComponent(*PerceptionComp);
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AimActor = PerceptionComp->GetClosesEnemy();

	auto DroneChar =Cast<ADroneCharacter>(GetPawn());
	auto HealthComponent = Cast<UHealthComponent>(DroneChar->GetComponentByClass(UHealthComponent::StaticClass()));

	
	SetFocus(AimActor);
	



}

	
