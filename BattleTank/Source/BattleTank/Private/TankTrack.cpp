// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	TrackMaxDrivingForce = 400000;
	PrimaryComponentTick.bCanEverTick = true;
	CurrentThrottle = 0;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector CorrectAcceleration = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	auto Tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (Tank->GetMass() * CorrectAcceleration) / 2;
	Tank->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle += FMath::Clamp(Throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * (CurrentThrottle * TrackMaxDrivingForce);
	auto ControlledTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	ControlledTank->AddForceAtLocation(ForceApplied, GetComponentLocation());
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0;
}

