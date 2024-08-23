
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePuckUp.generated.h"

class  UStaticMeshComponent;

UCLASS()
class DRONEGAME_API ABasePuckUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePuckUp();
	USceneComponent* SceneComponent;


	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float RespawnTime =5.0f;

	FTimerHandle RespawnTimerHandle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
	void Respawn();
	void PickUpWasTaken();
	bool CouldBeTaken();

};
