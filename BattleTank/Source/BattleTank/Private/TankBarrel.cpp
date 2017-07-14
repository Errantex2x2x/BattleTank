// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

UTankBarrel::UTankBarrel()
{
	MaxDegreesElevation = 30;
	MinDegreesElevation = 0;
	MaxDegreesPerSecond = 30;
}

void UTankBarrel::Elevate(float RelativeSpeed)
{
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp(NewElevation, MinDegreesElevation, MaxDegreesElevation);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));

}
