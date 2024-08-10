// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSphere.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/DebugDrawComponent.h"
#include "Engine/EngineTypes.h"
// Sets default values
ADamageSphere::ADamageSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);


}

// Called when the game starts or when spawned
void ADamageSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(),GetActorLocation(),300.0f,50,FColor::Black);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 1.0f, GetActorLocation(), 300.0f, nullptr,
		{}, this, nullptr,true);

}

