// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


UTankTurret::UTankTurret()
{
	MaxDegreesPerSecond = 30;
}

void UTankTurret::ChangeAzimuth(float RelativeSpeed)
{
	float AzimuthChange = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewYaw = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, NewYaw, 0));
}


