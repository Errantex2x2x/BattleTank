// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LifeSpanAfterHit = 2;
	ProjectileDamage = 20;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlastParticles"));

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlastParticles"));
	ImpactBlast->bAutoActivate = false;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComponent"));
	MovementComponent->bAutoActivate = false;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(FName("RadialForce"));
	RadialForce->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	UStaticMeshComponent * MeshComp = Cast<UStaticMeshComponent>(RootComponent);
	MeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	LaunchBlast->SnapTo(RootComponent);
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast->SnapTo(RootComponent);
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	RadialForce->SnapTo(RootComponent);
	RadialForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed)
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();

	LaunchBlast->Activate(true);
	LaunchBlast->ActivateSystem(true);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), RadialForce->Radius, UDamageType::StaticClass(), TArray<AActor *>());

	ImpactBlast->Activate(true);
	RadialForce->Activate(true);
	RadialForce->FireImpulse();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	GetWorld()->GetTimerManager().SetTimer(DeathHandle,this, &AProjectile::DeathTimerExpired, LifeSpanAfterHit, false);
}

void AProjectile::DeathTimerExpired()
{
	Destroy();
}

