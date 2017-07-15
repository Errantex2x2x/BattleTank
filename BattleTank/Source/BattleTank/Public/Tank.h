// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Aim at location
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float FireCoolDownSeconds;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetComponentsReference(UTankBarrel * InBarrel, UTankTurret * InTurret);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float LastFireTime = 0;

	UTankAimingComponent * TankAimingComponent = nullptr;

	UTankBarrel * Barrel;
};
