// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * InTrackL, UTankTrack* InTrackR)
{
	TrackL = InTrackL;
	TrackR = InTrackR;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move: %f"), Throttle)
	TrackL->SetThrottle(Throw);
	TrackR->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	TrackR->SetThrottle(-Throw);
	TrackL->SetThrottle(Throw);
}
