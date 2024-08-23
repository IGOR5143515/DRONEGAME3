// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootingComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootingComponent();
	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem *NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName="TraceTarget";

	float TraceMaxDistance = 2000;


	UFUNCTION(BlueprintCallable, Category = "Bullets")
	float GetBullets() { return Bullets; };
	void SetBullets(float Value) { Bullets = Value; }
	bool CanFire() { return Bullets > 0.0f; }
	float GetMaxBullets() { return MaxBullets; }
	float MaxBullets;
	float Damage = 10;
	float GetPertcent() { return Bullets / MaxBullets; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float Bullets;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartFire();
	void StopFire();
	void Shoot();
	void SpawnNiagara(FHitResult& HResult);
	void SpawnTraceFX(FVector& TraceStart, FVector& TraceEnd);
	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);
	AController* GetPlayerController();
};
