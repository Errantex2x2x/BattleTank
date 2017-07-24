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
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrel * InBarrel, UTankTurret * InTurret);
	
	UFUNCTION(BlueprintCallable)
	void Fire();
	
	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmo() const;

	void AimAt(FVector HitLocation);

protected:
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel * Barrel;
	UTankTurret * Turret;

	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float FireCoolDownSeconds;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int MaxAmmo;

	int CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus;

	//Used to know if the barrel is currently moving
	FVector LastBarrelForward;

};
