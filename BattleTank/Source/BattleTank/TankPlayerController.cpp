// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	CrosshairXLocation = 0.5f;
	CrosshairYLocation = 0.33333f;
	LineTraceRange = 1000000;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControllerTank()) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControllerTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLoc = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);
	FVector WorldLoc;//Useless
	FVector WorldDir;
	if (DeprojectScreenPositionToWorld(ScreenLoc.X, ScreenLoc.Y, WorldLoc, WorldDir))//Gets direction basing on screen position
	{
		return GetLookVectorHitLocation(WorldDir, OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldDir, FVector & OutHitLocation) const
{
	FHitResult HitRes;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(HitRes, StartLocation, StartLocation + WorldDir * LineTraceRange, ECC_Visibility))
	{
		OutHitLocation = HitRes.Location;
		return true;
	}
	else
		return false;
}
