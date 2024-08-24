// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneCharacter.h"
#include "AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class DRONEGAME_API AAICharacter : public ADroneCharacter
{
	GENERATED_BODY()
protected:
	virtual void OnDeath()override;
	virtual void BeginPlay()override;
	
public:
	AAICharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaivorTree;

};
