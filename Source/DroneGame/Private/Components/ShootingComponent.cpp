#include "Components/ShootingComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
	auto Character = Cast<ACharacter>(GetOwner());


	auto PlayerController = Character->GetController<APlayerController>();

	FVector Location;
	FRotator Rotation;

	PlayerController->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector Direction = Rotation.Vector();

	float TraceDistance = 1000.0f;

	FVector End = Location + (Direction * TraceDistance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

	if (HitResult.bBlockingHit) {

		auto Actor = HitResult.GetActor();
		Actor->TakeDamage(10.0f, FDamageEvent{}, Actor->GetInstigatorController(), Actor);
	}
}


