// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	TrackMaxDrivingForce = 400000;
}

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * (FMath::Clamp(Throttle, -1.0f, 1.0f) * TrackMaxDrivingForce);
	auto ControlledTank = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
	ControlledTank->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
