#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	auto act = GetOwner();
	if (!act)return;

	act->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::OnTakeAnyDamageHandle);
}



void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy, 
	AActor* DamageCauser)
{
	if (IsDead()) {
		OnDeath.Broadcast();
		return;
	}


	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	
	if (IsDead()) {	// Is dead?
		OnDeath.Broadcast();
	}
}

