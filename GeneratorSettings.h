// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GeneratorSettings.generated.h"

UCLASS()
class GRIDGENERATOR_API AGeneratorSettings : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorSettings();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int grid_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int grid_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "8x8 Buildings")
	int max_nmb_8_8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "16x8 Buildings")
	int max_nmb_16_8;
};
