// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		ATank * GetControllerTank() const;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange;

private:
	//Moves tank barrel so that it points towards the crosshair
	void AimTowardsCrosshair();
	//Returns wether we are aiming towards a collider, if true we load the location in the given variable
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector WorldDir, FVector & OutHitLocation) const;
};
