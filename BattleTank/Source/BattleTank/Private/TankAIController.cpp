// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	AimingComponent->AimAt(GetEnemyTank()->GetActorLocation());
	AimingComponent->Fire();
	MoveToActor(GetEnemyTank(),5);
}

ATank * ATankAIController::GetEnemyTank() const
{
	APlayerController * pc = GetWorld()->GetFirstPlayerController();
	if (pc && pc->IsA(ATankPlayerController::StaticClass()))
		return (Cast<ATankPlayerController>(pc))->GetControllerTank();
	else
		return nullptr;
}
