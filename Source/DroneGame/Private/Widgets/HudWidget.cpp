


#include "Widgets/HudWidget.h"
#include "Components/HealthComponent.h"

float UHudWidget::GetHealthPercent() const
{
	auto Player = GetOwningPlayerPawn();
	if (!Player)return 0.0f;


	auto HalthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HalthComponent)return 0.0f;

	return HalthComponent->GetPercent();
}
