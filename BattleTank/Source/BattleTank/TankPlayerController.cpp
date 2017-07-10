// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank * ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("Possessing %s"), *GetControllerTank()->GetName());
}
