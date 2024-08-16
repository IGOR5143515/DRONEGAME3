// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/HealthComponent.h"
#include "Components/ShootingComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"   
#include "MyAIController.h"
#include "Components/MyAIPerceptionComponent.h"



ADroneCharacter::ADroneCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingMovement");
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(CameraComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");


	ShootComponent = CreateDefaultSubobject<UShootingComponent>("ShootComponent");


	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}


void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnDeath.AddUObject(this, &ADroneCharacter::OnDeath);
	

	check(FloatingMovement);
	check(CameraComponent);
	check(SpringArmComponent);
	check(ShootComponent);
}


void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	
}

void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveUp",this, &ADroneCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveForward", this, &ADroneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADroneCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	PlayerInputComponent->BindAction("HitButton", IE_Pressed, ShootComponent, &UShootingComponent::StartFire);
	PlayerInputComponent->BindAction("HitButton", IE_Released, ShootComponent, &UShootingComponent::StopFire);



}

void ADroneCharacter::MoveUp(float Value)
{
	AddMovementInput(GetActorUpVector(), Value,true);
	
}

void ADroneCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value,true);

}

void ADroneCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ADroneCharacter::OnDeath()
{
	
	ShootComponent->StopFire();
	DisableInput(nullptr);	
	GetCapsuleComponent()->SetSimulatePhysics(true);
	

}


