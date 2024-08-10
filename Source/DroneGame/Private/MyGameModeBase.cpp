// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "DroneCharacter.h"
#include "MyPlayerController.h"
AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = ADroneCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

}
