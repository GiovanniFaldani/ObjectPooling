// Fill out your copyright notice in the Description page of Project Settings.


#include "Confetti.h"

// Sets default values
AConfetti::AConfetti()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add sphere mesh component and collision to simulate confetti, zero mass so it doesn't disrupt movement
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->InitSphereRadius(1.f);

	// Players can't walk on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	// Enable simulated physics
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionProfileName(TEXT("PhysicsActor"));

	// Set as root component
	RootComponent = CollisionComponent;

	// Create mesh to visualize confetti
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(CollisionComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	MeshComponent->SetStaticMesh(SphereMeshAsset.Object);
	MeshComponent->SetRelativeScale3D(FVector(.02f, .02f, .02f));
}

// Called when the game starts or when spawned
void AConfetti::BeginPlay()
{
	Super::BeginPlay();

	// Set random color here
	
}

// Called every frame
void AConfetti::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

