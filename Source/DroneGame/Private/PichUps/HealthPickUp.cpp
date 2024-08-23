// Fill out your copyright notice in the Description page of Project Settings.


#include "PichUps/HealthPickUp.h"
#include "DroneCharacter.h"
#include "Components/HealthComponent.h"

void AHealthPickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	auto Character = Cast<ADroneCharacter>(OtherActor);
	if (!Character)return;

	auto HealthComponent =Cast<UHealthComponent>( Character->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent)return;

	if (HealthComponent->GetHealth() == 100.0f)
		return;


	auto CurrentHealth = HealthComponent->GetHealth();

	CurrentHealth = FMath::Clamp(CurrentHealth + 20.0f, 0.0f, 100.0f);
	HealthComponent->SetHealth(CurrentHealth);


	UE_LOG(LogTemp, Error, TEXT("Health- %f"), HealthComponent->GetHealth());


}
