// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"




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

void ATankAIController::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("AI controller possessing %s "), *GetControllerTank()->GetName());
	UE_LOG(LogTemp, Log, TEXT("AI WILL DESTROY %s "), *GetEnemyTank()->GetName());
}
