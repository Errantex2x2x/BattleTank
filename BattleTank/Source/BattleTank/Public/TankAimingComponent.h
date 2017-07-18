// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus: uint8
{
	Aiming,
	Locked,
	Reloading
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrel * InBarrel, UTankTurret * InTurret);

	void Fire();
	void AimAt(FVector HitLocation);

protected:
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

	UTankBarrel * Barrel;
	UTankTurret * Turret;

	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float FireCoolDownSeconds;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus;
};
