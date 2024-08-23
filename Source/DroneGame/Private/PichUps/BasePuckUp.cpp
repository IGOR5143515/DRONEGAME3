// Fill out your copyright notice in the Description page of Project Settings.


#include "PichUps/BasePuckUp.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
ABasePuckUp::ABasePuckUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void ABasePuckUp::BeginPlay()
{
	Super::BeginPlay();
	
	check(Mesh);
}

// Called every frame
void ABasePuckUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator RotationDelta = FRotator(0, 100 * DeltaTime, 0);
	FQuat QuatRotation = FQuat(RotationDelta);

	Mesh->AddLocalRotation(QuatRotation);

}

void ABasePuckUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	

	PickUpWasTaken();
}

void ABasePuckUp::Respawn()
{

	if (GetRootComponent()) {
		GetRootComponent()->SetVisibility(true, true);
	}
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void ABasePuckUp::PickUpWasTaken()
{
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	if (GetRootComponent()) {
	GetRootComponent()->SetVisibility(false, true);
	}

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePuckUp::Respawn, RespawnTime);


}

bool ABasePuckUp::CouldBeTaken()
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

