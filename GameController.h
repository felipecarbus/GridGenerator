// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Tile.h"
#include "Tile_1_1.h"
#include "PlayerCharacter.h"
#include "GameController.generated.h"

UCLASS()
class GRIDGENERATOR_API AGameController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	TArray<FVector2D*> Grid;
	TArray<ATile_1_1*> Tiles;

	int grid_X;
	int grid_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Character")
	TSubclassOf<APlayerCharacter> Player_Character;

	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Character")
	TSubclassOf<ATile_1_1> Tile_BP;

	void LoadGrid(int grid_X, int grid_Y);
	void SpawnPlayerCharacter();
	void SpawnTiles();
	void HighLightPath(TArray<FVector2D*> _tilesCoordinates);
};
