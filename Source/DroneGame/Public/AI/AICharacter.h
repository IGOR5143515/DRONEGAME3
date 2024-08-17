// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AAICharacter : public ADroneCharacter
{
	GENERATED_BODY()
protected:
	virtual void OnDeath()override;
	virtual void BeginPlay()override;
	
};
