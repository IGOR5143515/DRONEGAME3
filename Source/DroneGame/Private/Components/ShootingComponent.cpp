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
	MaxBullets = 100.0f;
	Bullets =  MaxBullets;

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
	if (CanFire()) {
		if (GetWorld()) {
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UShootingComponent::Shoot, 0.05f, true);
		}
		Shoot();

	}
}

void UShootingComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UShootingComponent::Shoot()
{

	
	if (Bullets > 0.0f) {
		
		Bullets = FMath::Clamp(Bullets - 1, 0.0f, MaxBullets);

		if (!CanFire()) {
			StopFire();
		}
	}

	
	
	const auto Controller = GetPlayerController();
	if (!Controller)return;

	auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)return;
	
	FVector Muzzlestart = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
	FVector VievLocation;
	FRotator VeievRotaion;
	Controller->GetPlayerViewPoint(VievLocation, VeievRotaion);
	

	FTransform SocketTransform = Character->GetMesh()->GetSocketTransform(MuzzleSocketName);
	FVector TraceStart = VievLocation;

	FVector Dir = VeievRotaion.Vector();
	FVector TraceEnd = TraceStart + (Dir * TraceMaxDistance);
	


	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;

	if (HitResult.bBlockingHit) {

		TraceFXEnd = HitResult.ImpactPoint;
		SpawnNiagara(HitResult);
		AActor* Actor = HitResult.GetActor();
		if (!Actor)return;
		Actor->TakeDamage(Damage, FDamageEvent(), GetPlayerController(), Actor);
		
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

void UShootingComponent::MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}




AController* UShootingComponent::GetPlayerController()
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}


