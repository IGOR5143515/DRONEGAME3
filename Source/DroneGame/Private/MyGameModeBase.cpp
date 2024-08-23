// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "DroneCharacter.h"
#include "MyAIController.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = ADroneCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
}

UClass* AMyGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AMyAIController>()) {
		return AIPawnClass;
	}
	else
		return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMyGameModeBase::SpawnBots()
{
	if (!GetWorld())return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController=GetWorld()->SpawnActor<AMyAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
	
}
