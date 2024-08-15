// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyAIPerceptionComponent.h"
#include "Components/HealthComponent.h"
#include "AIController.h"
#include "Perception/AISense_Sight.h"

AActor* UMyAIPerceptionComponent::GetClosesEnemy()
{

	TArray<AActor*>Actors;

	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Actors);

	if (Actors.Num() == 0)return nullptr;

	auto controller = Cast<AAIController>(GetOwner());
	if (!controller)return nullptr;
	auto Pawn = controller->GetPawn();
	if (!Pawn)return nullptr;


	float BestDistance = MAX_FLT;

	AActor* Temp= nullptr;

	for (auto TempActor : Actors) {

		const auto HealthComponent = Cast<UHealthComponent>( TempActor->GetComponentByClass(UHealthComponent::StaticClass()));

		if (HealthComponent && !HealthComponent->IsDead()) {
			auto CurrentDistance = (TempActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance) {
				BestDistance = CurrentDistance;
				Temp = TempActor;
				}
			}

	}
	return Temp;
}
