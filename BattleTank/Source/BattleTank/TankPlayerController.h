// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
class UTank;
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


	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void AimingComponentFound(UTankAimingComponent * AimingComponentRef);


	virtual void SetPawn(APawn* InPawn) override;

private:
	//Moves tank barrel so that it points towards the crosshair
	void AimTowardsCrosshair();
	//Returns wether we are aiming towards a collider, if true we load the location in the given variable
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector WorldDir, FVector & OutHitLocation) const;

	UFUNCTION()
	void OnPawnDeath();

	UTankAimingComponent * AimingComponent;
};
