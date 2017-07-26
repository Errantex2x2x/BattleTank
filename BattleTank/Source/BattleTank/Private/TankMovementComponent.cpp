// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * InTrackL, UTankTrack* InTrackR)
{
	AISpeedMultiplier = 10;
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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector CurrentDirection = GetOwner()->GetActorForwardVector();

	IntendMoveForward(FVector::DotProduct(AIForwardIntention, CurrentDirection) * AISpeedMultiplier);
	IntendTurn(FVector::CrossProduct(CurrentDirection, AIForwardIntention).Z * AISpeedMultiplier);

	//UE_LOG(LogTemp, Log, TEXT("Requested move: %f"), FVector::DotProduct(AIForwardIntention, CurrentDirection));
}

