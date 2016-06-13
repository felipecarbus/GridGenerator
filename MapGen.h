// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Tile.h"
#include "Tile_8_8.h"
#include "Tile_16_8.h"
#include "RoadGen.h"
#include "GameController.h"
#include "MapGen.generated.h"

USTRUCT()
struct FAssetInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int x;

	UPROPERTY()
	int y;

	UPROPERTY()
	EBuildingType TypeOfBuilding;

	UPROPERTY()
	int buildingMesh;

	UPROPERTY()
	int roadType;

	//Roll
	UPROPERTY()
	int rotatorX;

	//Pitch
	UPROPERTY()
	int rotatorY;

	//Yaw
	UPROPERTY()
	int rotatorZ;
};

UCLASS()
class GRIDGENERATOR_API AMapGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGen();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float gridX = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float gridY = 4;

	//The measure to position all the assets
	float positionBase = 490;

	//The 2D Array of the Grid Coordinates
	TArray<FVector2D*> MapGrid;

	//The 2D Array of the Grid Coordinates of the current building. This is used to check if all the spots in the building can be placed in the current tile and adjacent ones
	TArray<FVector2D*> CurrentBuildingTileArray;

	//The 2D Array of the Grid Coordinates that contain tiles that are occupied by buildings
	TArray<FVector2D*> OccupiedTileArray;

	//The 2D Array of the Grid Coordinates with the coordinates of adjacent tiles of buildings. This is used to avoid buildings clamping together, thus creating room for roads
	TArray<FVector2D*> OccupiedBordersArray;

	//The 2D Array to check adjacent Tiles
	TArray<FVector2D*> Vectors_8_8;

	//The 2D Array to check adjacent Tiles
	TArray<FVector2D*> Vectors_16_8_Vertical;

	//The 2D Array to check adjacent Tiles
	TArray<FVector2D*> Vectors_16_8_Horizontal;

	//The 2D Array of the 8x8 Borders
	TArray<FVector2D*> Vectors_8_8_Border;

	//The 2D Array of the 8x8 Borders
	TArray<FVector2D*> Vectors_16_8_Vertical_Border;

	//The 2D Array of the 8x8 Borders
	TArray<FVector2D*> Vectors_16_8_Horizontal_Border;

	//The Array of all the buildings, roads and etc
	TArray<ATile*> MapAssets;

	//A Temporary array to store the information from the Road Gen class
	TArray<ATile*> TempRoadAssets;
	TArray<FVector2D*> TempBuildingBorderGridArray;
	TArray<FVector2D*> TempOccupiedGridArray;
	TArray<FVector2D*> TempRoadArray;
	TArray<FAssetInfo> AssetInfoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Classes")
	TSubclassOf<ATile> Building_8_8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Classes")
	TSubclassOf<ATile> Building_16_8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class")
	TSubclassOf<ATile> Road_4_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Classes")
	TSubclassOf<ARoadGen> Road_Generator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	TArray<UStaticMesh*> BuildingsMesh_16_8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	TArray<UStaticMesh*> BuildingsMesh_8_8;

	ARoadGen* RoadGenerator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Controller")
	TSubclassOf<AGameController> Game_Controller;

	AGameController* GameController;

	//Command to generate the full map without the steps
	UFUNCTION(BlueprintCallable, Category = "Map Creation")
	void GenerateFullMap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int chanceToPlaceBuildingMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int chanceToPlaceBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int selectBuildingChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int selectBuildingChanceMax;

	//The current number of 9x8 buildings placed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int NmbOf8x8Buildings;

	//The max number of 8x8 buildings placed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int MaxNmbOf8x8Buildings;

	//The current number of 16x8 buildings placed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int NmbOf16x8Buildings;

	//The max number of 16x8 buildings placed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	int MaxNmbOf16x8Buildings;

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<FVector2D> ReturnBorderTiles();

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<FVector2D> ReturnOccupiedTiles();

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<FVector2D> Return2DGrid();

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<ATile*> ReturnMapAssets();


	//Clean all the assets in the current stag, this function is called outside by the UI
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void CleanMap();

	//Sets the max ammount of building that can be placed, this function is called outside by the UI
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void SelectDensity(int _densityMultiplier);

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	int ReturnNmb8x8();

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	int ReturnNmb16x8();

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	void UIPlaceBuildings();

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	void UIPlaceRoads();

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	void UIPlaceParks();

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	void UISetRoads();

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	void UISaveAssets(FString _mapName);

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	TArray<FString> UILoadMapAssets();

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	void UILoadMap(FString mapName);

	UFUNCTION(BlueprintCallable, Category = "UI Command")
	void UIStartGame();

	void UICreateMiniMap(FString mapName);

	void SaveToFile(FString fileName);


private:
	//Code by staticvoidlol  https://answers.unrealengine.com/questions/212791/how-to-get-file-list-in-a-directory.html
	static TArray<FString> GetAllFilesInDirectory(const FString directory, const bool fullPath = true, const FString onlyFilesStartingWith = TEXT(""), const FString onlyFilesEndingWith = TEXT(""));

	//Json containing information of the map
	TSharedPtr<FJsonObject> SaveData;

	//Generate the 2D Grid to be the base of the system
	void GenerateGrid();

	//Add the 8x8 or 16x8 blocks to the map
	void AddBigBuildings();

	//Sets the type of tile to be placed, 8x8 or 16x8
	int TypeOfBuilding();

	//Add the coordinates of the current building tiles to the CurrentBuilding array
	bool CreateBuildingTiles(int _typeOfBuilding);

	//Checks if the Tile is Occupied by other buildings or borders
	void CheckIfTileIsOccupied(int _typeOfBuilding);

	//Checks if the building will be positioned within the grid, if not returns. This is used to prevent buildings from going out the grid
	void CheckIfOnGrid();

	//Spawns the Building blueprint into the world, after all the verifications.
	void SpawnBigBuilding(int typeOfBuilding);

	//After spawning the building, add the border coordinates to the border occupied array
	void AddBuildingBorder(int _typeOfBuilding);

	//After spawning the building, add the current building coordinates to the border occupied array
	void AddOccupiedTile();

	//Selects a random mesh inside an Array of building models
	void SelectMesh(int _typeOfBuilding);

	void CreateRoadGenerator();

	void SpawnAssetsFromLevel(TArray<FAssetInfo> _data);

	FRotator* ReturnRotator(int _typeOfBuilding);

	FVector2D* currentTile;

	//Check if a building can be positioned
	bool bBigBuilding;

	//Check if a building can be positioned
	bool bTileOccupied;

	//Check if the current building is on the grid
	bool bOnGrid;

	bool bReplacePark = false;

	//The model of building to be positioned
	UPROPERTY()
	UStaticMesh* BuildingModel;	
};
