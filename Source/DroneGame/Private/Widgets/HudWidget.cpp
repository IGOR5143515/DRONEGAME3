


#include "Widgets/HudWidget.h"
#include "Components/HealthComponent.h"
#include "Components/ShootingComponent.h"

float UHudWidget::GetHealthPercent() const
{
	auto Player = GetOwningPlayerPawn();
	if (!Player)return 0.0f;


	auto HalthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HalthComponent)return 0.0f;

	return HalthComponent->GetPercent();
}

float UHudWidget::GetAmmo()
{
	
	auto Player = GetOwningPlayerPawn();
	if (!Player)return 0.0f;

	auto ShootComp = Cast<UShootingComponent>(Player->GetComponentByClass(UShootingComponent::StaticClass()));
	if (!ShootComp)return 0.0f;

	return ShootComp->GetBullets();

}

float UHudWidget::GetMaxBullets()
{
	auto Player = GetOwningPlayerPawn();
	if (!Player)return 0.0f;

	auto ShootComp = Cast<UShootingComponent>(Player->GetComponentByClass(UShootingComponent::StaticClass()));
	if (!ShootComp)return 0.0f;

	return ShootComp->GetMaxBullets();
}
