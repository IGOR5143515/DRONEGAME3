// Fill out your copyright notice in the Description page of Project Settings.


#include "PichUps/AmmoPickUp.h"
#include "Components/ShootingComponent.h"
#include "DroneCharacter.h"

void AAmmoPickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	auto Character = Cast<ADroneCharacter>(OtherActor);
	if (!Character)return;

	auto ShootComponent = Cast<UShootingComponent>(Character->GetComponentByClass(UShootingComponent::StaticClass()));
	if (!ShootComponent)return;

	float CurrentAmmo = ShootComponent->GetBullets();
	


	CurrentAmmo = FMath::Clamp(CurrentAmmo + 25, 0.0f, 100.0f);
	ShootComponent->SetBullets(CurrentAmmo);

	UE_LOG(LogTemp, Error, TEXT("%f - Ammo"), ShootComponent->GetBullets());

}
