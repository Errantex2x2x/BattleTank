// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
	StartingHealth = 100;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DmgTaken = FMath::Clamp(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
	UE_LOG(LogTemp, Log, TEXT("DAMAGE! %i"), DmgTaken);
	CurrentHealth -= DmgTaken;
	return DmgTaken;
}
