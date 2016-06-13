// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Tile.h"
#include "Tile_4_4.h"
#include "RoadGen.generated.h"

UCLASS()
class GRIDGENERATOR_API ARoadGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadGen();

	//The Map 2D Grid
	TArray<FVector2D*> Road2DGrid;

	//The Coordinates of Occupied tiles
	TArray<FVector2D*> OccupiedGridArray;

	//The Coordinates of Building Borders
	TArray<FVector2D*> BuildingBorderGridArray;

	//The Array of 4x4 Roads
	TArray<FVector2D*> RoadArray;

	TArray<FVector2D*> RoadArrayIndexToRemove;

	//The Coordinates to fill the 8 squares around a tile
	TArray<FVector2D*> Coordinates_8_Around;

	//Coordinate to send to the BP Object
	TArray<FVector2D*> Coordinates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class")
	TSubclassOf<ATile> Road_4_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Base")
	float positionBase;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void LoadAssets(TArray<FVector2D*> _2DGrid, TArray<FVector2D*> _OccupiedGridArray, TArray<FVector2D*> _BuildingBorderGridArray);

	void GenerateFullRoadAssets();

	void FillEmptySpaces();
	
	void SpawnRoad();

	void EmptyAssets();
	
	void Clean_4_4();
	void CleanArray();
	void GenerateRoads();

	TArray<ATile*> ReturnRoadAssets();
	void SetRoadAssets(TArray<ATile*> _roadAssets);

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<FVector2D> ReturnOccupiedTiles();

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<FVector2D> ReturnRoadArray();

private:

	TArray<ATile*> RoadAssets;



	//Checkf it the coordinate is available
	bool bTileOccupied;

	bool bNorthAvaiable;
	bool bEastAvaiable;
	bool bWestAvaiable;
	bool bSouthAvaiable;

	TArray<int> directions;
	TArray<FVector2D> NWSEDirections;

	FVector2D* currentTile;

	//current road, used to clean the the 4x4 tiles
	FVector2D* currentRoad;

	//current park, used to spawn the first park tile
	FVector2D* currentPark;

	//used to spawn the second park tile
	FVector2D* nextPark;

	
	bool CheckIfOnGrid(FVector2D tile);
	bool CheckIfSpotIsAvailable(FVector2D tile);
	void SpawnParks(int _randomDir);
	void AddOccupiedTilesAround(FVector2D* _tile);
	void CheckMapAssets(FVector2D* _park, ATile* _parkTile);
	void RemoveFromRoadArray(FVector2D* _tile);
	void ChangeRoad(FVector2D coordinate, int roadType);
};
