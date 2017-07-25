// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UProjectileMovementComponent * MovementComponent;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent * CollisionMesh;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent * LaunchBlast; 
		UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent * ImpactBlast;
		UPROPERTY(VisibleAnywhere)
			URadialForceComponent * RadialForce;
};
