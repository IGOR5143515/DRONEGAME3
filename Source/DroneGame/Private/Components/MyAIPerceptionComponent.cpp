// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyAIPerceptionComponent.h"
#include "Components/HealthComponent.h"
#include "AIController.h"
#include "Perception/AISense_Sight.h"
#include "CharacterPlayerState.h"



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

		auto PercievePawn = Cast<APawn>(TempActor);
		bool Enemies = PercievePawn && AreEnemies(controller, PercievePawn->Controller);
		const auto HealthComponent = Cast<UHealthComponent>( TempActor->GetComponentByClass(UHealthComponent::StaticClass()));

		if (HealthComponent && !HealthComponent->IsDead()&& Enemies) {
			auto CurrentDistance = (TempActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance) {
				BestDistance = CurrentDistance;
				Temp = TempActor;
				}
			}

	}
	return Temp;
}

bool UMyAIPerceptionComponent::AreEnemies(AController* Controller1, AController* Controller2)
{

	if (!Controller1 || !Controller2 || Controller1 == Controller2)return false;

	auto PlayerState1 = Cast<ACharacterPlayerState>(Controller1->PlayerState);
	auto PlayerState2 = Cast<ACharacterPlayerState>(Controller2->PlayerState);

	return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();

}
