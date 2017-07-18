// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	GetControllerTank()->AimAt(GetEnemyTank()->GetActorLocation());
	GetControllerTank()->Fire();
	MoveToActor(GetEnemyTank(),5);
}

ATank * ATankAIController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetEnemyTank() const
{
	APlayerController * pc = GetWorld()->GetFirstPlayerController();
	if (pc && pc->IsA(ATankPlayerController::StaticClass()))
		return (Cast<ATankPlayerController>(pc))->GetControllerTank();
	else
		return nullptr;
}
