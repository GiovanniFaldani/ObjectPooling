// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfettiDispenser.h"
#include "../ObjectPoolSubsystem.h"
#include "Confetti.h"

// Sets default values
AConfettiDispenser::AConfettiDispenser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConfettiDispenser::BeginPlay()
{
	Super::BeginPlay();
	
	// Create object pool
	if (!GetWorld()) return;

	UObjectPoolSubsystem* MySubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();

	if (!MySubsystem) return;

	MySubsystem->AddPool(AConfetti::StaticClass(), ConfettiNumber);

	// Init timer
	ConfettiSpawnTimer = ConfettiSpawnInterval;

	return;
}

// Called every frame
void AConfettiDispenser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update timer
	if (ConfettiSpawnTimer > 0.f) {
		ConfettiSpawnTimer -= DeltaTime;

		if (ConfettiSpawnTimer <= 0.f)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Spawning Confetti"));

			// Spawn confetti
			if (!GetWorld()) return;
			UObjectPoolSubsystem* MySubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
			if (!MySubsystem) return;
			TScriptInterface<IObjectPoolInterface> ConfettiActorInterface = MySubsystem->GetObjectFromPool(AConfetti::StaticClass());
			if (ConfettiActorInterface)
			{
				AConfetti* ConfettiActor = Cast<AConfetti>(ConfettiActorInterface.GetObject());
				if (ConfettiActor)
				{
					FObjectPoolActivationData ActivationData;
					ActivationData.ObjectPoolTransform = FTransform(FRotator::ZeroRotator, SpawnLocation, FVector(1.f, 1.f, 1.f));
					ConfettiActorInterface->Activate(ActivationData);
					UE_LOGFMT(LogTemp, Display, "Activated a confetto from pool");
				}
			}
			// Reset timer
			ConfettiSpawnTimer = ConfettiSpawnInterval;
		}
	}
}

