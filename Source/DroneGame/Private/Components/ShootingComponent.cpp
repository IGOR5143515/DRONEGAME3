#include "Components/ShootingComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "DroneCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


UShootingComponent::UShootingComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}



void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}



void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UShootingComponent::StartFire()
{
	if (GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UShootingComponent::Shoot, 0.05f, true);
	}
	Shoot();

}

void UShootingComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UShootingComponent::Shoot()
{

	auto Character = Cast<ADroneCharacter>(GetOwner());
	auto PlayerController = Character->GetController<APlayerController>();

	FVector Muzzlestart = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);

	FVector Location;
	FRotator Rotation;

	if (Character->IsPlayerControlled()) {
		PlayerController->GetPlayerViewPoint(Location, Rotation);
	}
	else {
		Location = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
		Rotation = Character->GetMesh()->GetSocketRotation(MuzzleSocketName);
		UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *Rotation.ToString());
		}

	FVector Start = Location;
	FVector Direction = Rotation.Vector();
	
	float TraceDistance = 2000.0f;

	FVector End = Location + (Direction * TraceDistance);
	

	FVector TraceFXEnd = End;
	

	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
	if (HitResult.bBlockingHit) {

		TraceFXEnd = HitResult.ImpactPoint;
		auto Actor = HitResult.GetActor();
		SpawnNiagara(HitResult);
		Actor->TakeDamage(10.0f, FDamageEvent{}, Actor->GetInstigatorController(), Actor);
	}

	SpawnTraceFX(Muzzlestart, TraceFXEnd);
}

void UShootingComponent::SpawnNiagara(FHitResult& HResult)
{

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffect, HResult.ImpactPoint, HResult.ImpactNormal.Rotation());

}

void UShootingComponent::SpawnTraceFX(FVector& TraceStart, FVector& TraceEnd)
{
	auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX,
		TraceStart);
	if (TraceFXComponent) {
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}


