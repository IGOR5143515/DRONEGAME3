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
	

	const auto Controller = GetPlayerController();
	if (!Controller)return;

	auto Character = Cast<ACharacter>(GetOwner());

	
	FVector Muzzlestart = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
	FVector VievLocation;
	FRotator VeievRotaion;
	Controller->GetPlayerViewPoint(VievLocation, VeievRotaion);


	FTransform SocketTransform = Character->GetMesh()->GetSocketTransform(MuzzleSocketName);

	FVector TraceStart = VievLocation;

	auto BulletSpread = FMath::DegreesToRadians(1.5f);

	FVector ShootDirection = FMath::VRandCone(VeievRotaion.Vector(), BulletSpread);

	FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;


	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;

	if (HitResult.bBlockingHit) {

		TraceFXEnd = HitResult.ImpactPoint;

		SpawnNiagara(HitResult);
		AActor* Actor = HitResult.GetActor();
		if (!Actor)return;

		Actor->TakeDamage(1.0f, FDamageEvent(), GetPlayerController(), Actor);
		
	}



	//if (HitResult.bBlockingHit) {

	////	TraceFXEnd = HitResult.ImpactPoint;
	//	auto Actor = HitResult.GetActor();
	//	SpawnNiagara(HitResult);
	//	Actor->TakeDamage(10.0f, FDamageEvent{}, Actor->GetInstigatorController(), Actor);
	//}

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

void UShootingComponent::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	GetPlayerViewPoint(ViewLocation, ViewRotation);
	TraceStart = ViewLocation;
	FVector Direction = ViewRotation.Vector();
	TraceEnd = TraceStart + Direction * TraceMaxDistance;
}

bool UShootingComponent::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{

	auto Character = Cast<ACharacter>(GetOwner());

	if (Character->IsPlayerControlled()) {
		auto Controller = Character->GetController<APlayerController>();

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);


	}
	else
	{
		ViewLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
		ViewRotation = Character->GetMesh()->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

AController* UShootingComponent::GetPlayerController()
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}


