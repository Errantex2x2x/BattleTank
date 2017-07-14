// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * InBarrel)
{
	Barrel = InBarrel;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("FireHole");

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, Barrel->GetSocketLocation("FireHole"), HitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Log, TEXT("%s Aiming at %s from %s"), *GetOwner()->GetName(), *AimDirection.ToString(), Barrel ? *Barrel->GetComponentLocation().ToString() : *FVector::ZeroVector.ToString());
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator WantedRotation = AimDirection.Rotation();
	FRotator Delta = CurrentRotation - Delta;
	
	Barrel->Elevate(Delta.Pitch);
	//Barrel->GetForwardVector().Rotation(Quater)
}
