// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UTankAimingComponent::SetComponentsReference(UTankBarrel * InBarrel, UTankTurret * InTurret)
{
	Barrel = InBarrel;
	Turret = InTurret;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
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