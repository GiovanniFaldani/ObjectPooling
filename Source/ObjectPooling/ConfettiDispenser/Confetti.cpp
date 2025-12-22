// Fill out your copyright notice in the Description page of Project Settings.


#include "Confetti.h"
#include "../ObjectPoolSubsystem.h"


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

}

// Called every frame
void AConfetti::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (lifeTimer > 0.f) {
		lifeTimer -= DeltaTime;
		if (lifeTimer <= 0.f)
		{
			// Return to pool
			Deactivate();
			UE_LOGFMT(LogTemp, Display, "Deactivating object...");
		}
	}
}

void AConfetti::NativeActivate(FObjectPoolActivationData ObjectPoolData)
{
	Super::NativeActivate(ObjectPoolData);
	lifeTimer = lifeTime;
	this->SetActorTransform(ObjectPoolData.ObjectPoolTransform);

	// Set random color
	EConfettiColor RandomColor = static_cast<EConfettiColor>(FMath::RandRange(0, (int)EConfettiColor::Length));
	switch (RandomColor) {
	case EConfettiColor::Red:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_Red.MI_Red'")));
		break;
	case EConfettiColor::Blue:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_Blue.MI_Blue'")));
		break;
	case EConfettiColor::Green:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_Green.MI_Green'")));
		break;
	case EConfettiColor::Yellow:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_Yellow.MI_Yellow'")));
		break;
	case EConfettiColor::Purple:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_Purple.MI_Purple'")));
		break;
	case EConfettiColor::Orange:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_Orange.MI_Orange'")));
		break;
	case EConfettiColor::Pink:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_Pink.MI_Pink'")));
		break;
	case EConfettiColor::White:
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/ObjectPoolingSystem/Materials/MaterialInstances/MI_White.MI_White'")));
		break;
	}

	UE_LOGFMT(LogTemp, Display, "Added to pool `{Guid}`", GetActorGuid());
}

void AConfetti::NativeDeactivate()
{
	Super::NativeDeactivate();
	if (!GetWorld()) return;
	UObjectPoolSubsystem* MySubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
	if (!MySubsystem) return;
	MySubsystem->ReturnObjectToPool(AConfetti::StaticClass(), TScriptInterface<IObjectPoolInterface>(this));
	UE_LOGFMT(LogTemp, Display, "Returned to pool `{Guid}`", GetActorGuid());
}

