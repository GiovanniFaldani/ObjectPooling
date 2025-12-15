// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PoolActorBase.h"
#include "../ObjectPoolInterface.h"
#include "Components/SphereComponent.h"
#include "Confetti.generated.h"

UENUM(BlueprintType)
enum class EConfettiColor : uint8
{
	Red			UMETA(DisplayName = "Red"),
	Blue		UMETA(DisplayName = "Blue"),
	Green		UMETA(DisplayName = "Green"),
	Yellow		UMETA(DisplayName = "Yellow"),
	Purple		UMETA(DisplayName = "Purple"),
	Orange		UMETA(DisplayName = "Orange"),
	Pink		UMETA(DisplayName = "Pink"),
	White		UMETA(DisplayName = "White"),
	Length		UMETA(Hidden)
};

UCLASS()
class OBJECTPOOLING_API AConfetti : public APoolActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConfetti();

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Confetti")
	float lifeTime;

	// Confetti mesh
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Confetti")
	UStaticMeshComponent* MeshComponent;

	// Confetti collision
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Confetti")
	USphereComponent* CollisionComponent;

	float lifeTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void NativeActivate(FObjectPoolActivationData ObjectPoolData) override;

	virtual void NativeDeactivate() override;
};
