

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UHealthComponent();
	FOnDeath OnDeath;


protected:
	
	virtual void BeginPlay() override;
	float Health=0.0f;
	float MaxHealth = 100.0f;
public:	

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetPercent() { return Health / MaxHealth; }
	bool IsDead() { return Health <= 0.0f; }


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
