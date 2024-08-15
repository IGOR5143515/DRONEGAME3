// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Components/MyAIPerceptionComponent.h"

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
}
