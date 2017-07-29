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
	auto EnemyTank = GetEnemyTank();

	if (EnemyTank)
	{
		AimingComponent->AimAt(EnemyTank->GetActorLocation());

		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
			AimingComponent->Fire();

		MoveToActor(EnemyTank, 5);
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank * Tank = Cast<ATank> (InPawn);
		
		if (!Tank)
			return;

		Tank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPawnDeath);
	}

}

void ATankAIController::OnPawnDeath()
{
	//GetPawn()->SetLifeSpan(0.2f);
	GetPawn()->DetachFromControllerPendingDestroy();
	
}

ATank * ATankAIController::GetEnemyTank() const
{
	APlayerController * pc = GetWorld()->GetFirstPlayerController();
	if (pc && pc->IsA(ATankPlayerController::StaticClass()))
		return (Cast<ATankPlayerController>(pc))->GetControllerTank();
	else
		return nullptr;
}
