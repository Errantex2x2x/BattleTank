// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	ATank * GetEnemyTank() const;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn * InPawn) override;

	UFUNCTION()
	void OnPawnDeath();

private:
	UTankAimingComponent * AimingComponent;

};
