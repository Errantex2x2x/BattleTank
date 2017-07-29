// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
protected:
	GENERATED_BODY()
	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth;

	int32 CurrentHealth;

public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetPercentHealth() const;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
};
