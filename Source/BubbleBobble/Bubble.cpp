// Fill out your copyright notice in the Description page of Project Settings.
//https://docs.unrealengine.com/en-US/Programming/Tutorials/FirstPersonShooter/3/1/index.html

#include "Bubble.h"
#include "BubbleBobble.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"

#include "Engine/Engine.h"

// Sets default values
ABubble::ABubble()
{

	floating = false;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(70.0f);
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 2600.0f;
	ProjectileMovementComponent->MaxSpeed = 2600.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

}

void ABubble::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Called when the game starts or when spawned
void ABubble::BeginPlay()
{

	Super::BeginPlay();

	//Collision stuff
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABubble::OnOverlapBegin);

	// Call Float once (0.0f), starting two seconds from now.
	GetWorldTimerManager().SetTimer(floatTimer, this, &ABubble::Float, 1.0f, true, 0.3f);

}

void ABubble::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Enemy")) // Checks bubble is colliding with enemy
	{
		if (GEngine) /** Global engine pointer. Can be 0 so don't use without checking. */
		{
			GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::White, "ENEMY COLLISION");
			//OtherActor->Destroy();

			//Change Sprite

			this->Float();
		}

	}

}

void ABubble::Despawn()
{

	this->Destroy();

}

void ABubble::Float()
{

	GetWorldTimerManager().ClearTimer(floatTimer);
	floating = true;

	this->Despawn();

	//Start floating upwards
	//Stop Horizontal Movement

	//Start Upwards Movement

}

// Called every frame
void ABubble::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	//After a certain amount of time, Float


}
