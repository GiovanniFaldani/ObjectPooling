// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PoolActorBase.h"
#include "../ObjectPoolInterface.h"
#include "Components/SphereComponent.h"
#include "Confetti.generated.h"

UCLASS()
class OBJECTPOOLING_API AConfetti : public APoolActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConfetti();

protected:
	// Confetti mesh
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Confetti")
	UStaticMeshComponent* MeshComponent;

	// Confetti collision
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Confetti")
	USphereComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
