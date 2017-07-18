// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"



UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FiringStatus = EFiringStatus::Reloading;
	FireCoolDownSeconds = 1;
	LaunchSpeed = 4000;
}

void UTankAimingComponent::Initialize(UTankBarrel * InBarrel, UTankTurret * InTurret)
{
	Barrel = InBarrel;
	Turret = InTurret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("FireHole");

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, Barrel->GetSocketLocation("FireHole"), HitLocation, LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (GetWorld()->GetTimeSeconds() - LastFireTime > FireCoolDownSeconds)
	{
		LastFireTime = GetWorld()->GetTimeSeconds();
		AProjectile * Proj = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("FireHole"), Barrel->GetSocketRotation("FireHole"));
		Proj->LaunchProjectile(LaunchSpeed);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator WantedRotation = AimDirection.Rotation();
	FRotator Delta = WantedRotation - CurrentRotation;
	
	Barrel->Elevate(Delta.Pitch);
}


void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator WantedRotation = AimDirection.Rotation();
	float DeltaX = WantedRotation.Yaw - CurrentRotation.Yaw;

	if (DeltaX > 180.0f)
		DeltaX = DeltaX - 360;
	else if (DeltaX < -180.0f)
		DeltaX = DeltaX + 360;

	Turret->ChangeAzimuth(DeltaX);

}