// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankTrack * InTrackL, UTankTrack* InTrackR);

	UFUNCTION(BlueprintCallable)
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
		void IntendTurn(float Throw);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack * TrackL;
	UTankTrack * TrackR;

};
