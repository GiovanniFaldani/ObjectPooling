// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConfettiDispenser.generated.h"

UCLASS()
class OBJECTPOOLING_API AConfettiDispenser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConfettiDispenser();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Confetti Dispenser")
	int ConfettiNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Confetti Dispenser")
	FVector SpawnLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Confetti Dispenser")
	float ConfettiSpawnInterval;

	float ConfettiSpawnTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
