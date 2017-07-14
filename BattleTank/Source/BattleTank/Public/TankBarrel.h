// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds infos about tank's barrel
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankBarrel();
	void Elevate(float DegreesPerSecond);
	
private:
	UPROPERTY(Category = Setup, EditAnywhere)
		float MaxDegreesElevation;

	UPROPERTY(Category = Setup, EditAnywhere)
		float MinDegreesElevation;

	UPROPERTY(Category = Setup, EditAnywhere)
		float MaxDegreesPerSecond;

};
