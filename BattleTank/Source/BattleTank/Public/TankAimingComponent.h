// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();
	void SetComponentsReference(UTankBarrel * InBarrel, UTankTurret * InTurret);

protected:
	virtual void BeginPlay() override;
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

	UTankBarrel * Barrel;
	UTankTurret * Turret;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector HitLocation, float LaunchSpeed);	

};
