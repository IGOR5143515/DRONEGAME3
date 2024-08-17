// Fill out your copyright notice in the Description page of Project Settings.


#include "PichUps/BasePuckUp.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasePuckUp::ABasePuckUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void ABasePuckUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePuckUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePuckUp::NotifyActorBeginOverlap(AActor* OtherActor)
{

	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogTemp, Error, TEXT("sef"));
}

