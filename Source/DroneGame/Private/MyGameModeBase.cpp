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
	CurrentRound = 1;
	StartRound();

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

void AMyGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AMyGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AMyGameModeBase::GameTimerUpdate()
{

	UE_LOG(LogTemp, Error, TEXT("Time %i / Round %i / %i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	
	if (--RoundCountDown == 0) {
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum) {
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Game Ower"));
	}
}

void AMyGameModeBase::ResetPlayers()
{

	if (!GetWorld())return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It) {

		ResetOnePlayer(It->Get());
	}

}

void AMyGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetWorld()) {
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
}
