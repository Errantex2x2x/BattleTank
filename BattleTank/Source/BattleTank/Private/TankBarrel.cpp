// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

UTankBarrel::UTankBarrel()
{
	MaxDegreesElevation = 40;
	MinDegreesElevation = 0;
	MaxDegreesPerSecond = 30;
}

void UTankBarrel::Elevate(float RelativeSpeed)
{
	float ElevationChange = FMath::Clamp(RelativeSpeed,-1.0f,1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp(NewElevation, MinDegreesElevation, MaxDegreesElevation);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
