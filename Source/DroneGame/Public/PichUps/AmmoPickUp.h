// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PichUps/BasePuckUp.h"
#include "AmmoPickUp.generated.h"


UCLASS()
class DRONEGAME_API AAmmoPickUp : public ABasePuckUp
{
	GENERATED_BODY()
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
};
