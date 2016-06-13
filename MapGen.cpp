// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "JsonObjectConverter.h"
#include "MapGen.h"


// Sets default values
AMapGen::AMapGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapGen::BeginPlay()
{
	Super::BeginPlay();
	
	//Adds the 8x8 Building Vectors
	Vectors_8_8.Add(new FVector2D(0, 0));
	Vectors_8_8.Add(new FVector2D(1, 0));
	Vectors_8_8.Add(new FVector2D(0, 1));
	Vectors_8_8.Add(new FVector2D(1, 1));

	//Adds the 16x8 Vertical Building Vectors
	Vectors_16_8_Vertical.Add(new FVector2D(0, 0));
	Vectors_16_8_Vertical.Add(new FVector2D(0, 1));
	Vectors_16_8_Vertical.Add(new FVector2D(0, 2));
	Vectors_16_8_Vertical.Add(new FVector2D(0, 3));
	Vectors_16_8_Vertical.Add(new FVector2D(1, 0));
	Vectors_16_8_Vertical.Add(new FVector2D(1, 1));
	Vectors_16_8_Vertical.Add(new FVector2D(1, 2));
	Vectors_16_8_Vertical.Add(new FVector2D(1, 3));

	//Adds the 16x8 Horizontal Building Vectors
	Vectors_16_8_Horizontal.Add(new FVector2D(0, 0));
	Vectors_16_8_Horizontal.Add(new FVector2D(0, 1));
	Vectors_16_8_Horizontal.Add(new FVector2D(1, 0));
	Vectors_16_8_Horizontal.Add(new FVector2D(1, 1));
	Vectors_16_8_Horizontal.Add(new FVector2D(2, 0));
	Vectors_16_8_Horizontal.Add(new FVector2D(2, 1));
	Vectors_16_8_Horizontal.Add(new FVector2D(3, 0));
	Vectors_16_8_Horizontal.Add(new FVector2D(3, 1));

	//Adds the 8x8 Building Border Vectors
	Vectors_8_8_Border.Add(new FVector2D(-1, -1));
	Vectors_8_8_Border.Add(new FVector2D(-1, 0));
	Vectors_8_8_Border.Add(new FVector2D(-1, 1));
	Vectors_8_8_Border.Add(new FVector2D(-1, 2));
	Vectors_8_8_Border.Add(new FVector2D(0, -1));
	Vectors_8_8_Border.Add(new FVector2D(0, 2));
	Vectors_8_8_Border.Add(new FVector2D(1, -1));
	Vectors_8_8_Border.Add(new FVector2D(1, 2));
	Vectors_8_8_Border.Add(new FVector2D(2, -1));
	Vectors_8_8_Border.Add(new FVector2D(2, 0));
	Vectors_8_8_Border.Add(new FVector2D(2, 1));
	Vectors_8_8_Border.Add(new FVector2D(2, 2));

	//Adds the 16x8 Vertical Building Border Vectors
	Vectors_16_8_Vertical_Border.Add(new FVector2D(-1, -1));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(-1, 0));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(-1, 1));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(-1, 2));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(-1, 3));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(-1, 4));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(0, 1));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(0, 4));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(1, -1));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(1, 4));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(2, -1));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(2, 0));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(2, 1));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(2, 2));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(2, 3));
	Vectors_16_8_Vertical_Border.Add(new FVector2D(2, 4));

	//Adds the 16x8 Horizontal Building Border Vectors
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(-1, -1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(-1, 0));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(-1, 1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(-1, 2));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(0, -1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(0, 2));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(1, -1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(1, 2));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(2, -1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(2, 2));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(3, -1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(3, 2));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(4, -1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(4, 0));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(4, 1));
	Vectors_16_8_Horizontal_Border.Add(new FVector2D(4, 2));

	//GenerateFullMap();
}

// Called every frame
void AMapGen::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMapGen::GenerateFullMap()
{
	CleanMap();
	GenerateGrid();
	NmbOf8x8Buildings = MaxNmbOf8x8Buildings;
	NmbOf16x8Buildings = MaxNmbOf16x8Buildings;
	AddBigBuildings();
	CreateRoadGenerator();
	RoadGenerator->GenerateFullRoadAssets();
}

void AMapGen::GenerateGrid()
{
	for (int i = 0; i < gridX; i++)
	{
		for (int j = 0; j < gridY; j++)
		{
			FVector2D* gridPosition = new FVector2D(i,j);

			MapGrid.Add(gridPosition);
		}
	}
}

void AMapGen::AddBigBuildings()
{
	for (int i = 0; i < MapGrid.Num(); i++)
	{
		currentTile = MapGrid[i];

		int typeOfBuilding = TypeOfBuilding();

		if (bBigBuilding)
		{
			CheckIfTileIsOccupied(typeOfBuilding);

			if (!bTileOccupied)
			{
				//SelectMesh(typeOfBuilding);
				SpawnBigBuilding(typeOfBuilding);
				AddBuildingBorder(typeOfBuilding);
				AddOccupiedTile();
				if (typeOfBuilding==1)
					NmbOf8x8Buildings--;
				if (typeOfBuilding == 2 || typeOfBuilding == 3)
				{
					NmbOf16x8Buildings--;
				}
			}
		}
	}
}

int AMapGen::TypeOfBuilding()
{
	bBigBuilding = false;
	//typeOfBuilding = 0;

	//x 0->100
	int randomChance = FMath::RandRange(0, chanceToPlaceBuildingMax);
	// Low Density < 25 / Med Density < 50 / High Density < 75
	// x < 50
	if (randomChance < chanceToPlaceBuilding)
	{
		bBigBuilding = true;
		//x 0->100
		int typeToSelect = FMath::RandRange(0, selectBuildingChanceMax);

		//  66 < x < 100
		// 8x8 Selected
		if (typeToSelect < 100 && typeToSelect > 66 && NmbOf8x8Buildings > 0)
		{
			return 1;
		}
		//  33 < x < 66
		// 16x8 Selected Vertical
		else if (typeToSelect < 66 && typeToSelect > 33 && NmbOf16x8Buildings>0)
		{
			return 2;
		}
		//  x < 33
		// 16x8 Selected Horizontal
		else if (typeToSelect < 33 && NmbOf16x8Buildings>0)
		{
			return 3;
		}
		else
		{
			return 0;
		}
	}
	else
		return 0;

}

void AMapGen::CheckIfTileIsOccupied(int _typeOfBuilding)
{
	CurrentBuildingTileArray.Empty();
	bTileOccupied = false;

	//check if both the arrays are valid
	//if (OccupiedTileArray.Num() != 0 || OccupiedBordersArray.Num() != 0)
	//{
		//Assign the current building to it's coordinates
	bool checkIfOnGrid = CreateBuildingTiles(_typeOfBuilding);

	if (checkIfOnGrid)
	{
		for (int i = 0; i < OccupiedTileArray.Num(); i++)
		{
			for (int j = 0; j < CurrentBuildingTileArray.Num(); j++)
			{
				if (*OccupiedTileArray[i] == *CurrentBuildingTileArray[j])
				{
					bTileOccupied = true;
					return;
				}
			}
		}

		for (int i = 0; i < OccupiedBordersArray.Num(); i++)
		{
			for (int j = 0; j < CurrentBuildingTileArray.Num(); j++)
			{
				if (*OccupiedBordersArray[i] == *CurrentBuildingTileArray[j])
				{
					bTileOccupied = true;
					return;
				}
			}
		}
	}
	else
		bTileOccupied = true;
}

bool AMapGen::CreateBuildingTiles(int _typeOfBuilding)
{
	TArray<FVector2D*> vectorsToAdd;

	switch (_typeOfBuilding)
	{
	case 0:
		break;
	//8x8 Selected
	case 1:
		vectorsToAdd = Vectors_8_8;
		break;
	//16x8 Vertical Selected
	case 2:
		vectorsToAdd = Vectors_16_8_Vertical;
		break;
	//16x8 Horizontal Selected
	case 3:
		vectorsToAdd = Vectors_16_8_Horizontal;
		break;
	default:
		break;
	}

	for (int i = 0; i < vectorsToAdd.Num(); i++)
	{
		FVector2D* vectorToAdd = new FVector2D(vectorsToAdd[i]->X+currentTile->X, vectorsToAdd[i]->Y+currentTile->Y);

		if (vectorToAdd->X >= gridX)
		{
			return false;
		}

		if (vectorToAdd->Y >= gridY)
		{
			return false;
		}

		CurrentBuildingTileArray.Add(vectorToAdd);
	}
	return true;

}

void AMapGen::SelectMesh(int _typeOfBuilding)
{
	switch (_typeOfBuilding)
	{
	default:
		break;
	case 1:
		BuildingModel = BuildingsMesh_8_8[FMath::RandRange(0, BuildingsMesh_8_8.Num() - 1)];
		break;
	case 2:
		BuildingModel = BuildingsMesh_16_8[FMath::RandRange(0, BuildingsMesh_16_8.Num() - 1)];
		break;
	case 3:
		BuildingModel = BuildingsMesh_16_8[FMath::RandRange(0, BuildingsMesh_16_8.Num() - 1)];
		break;
	}
}

void AMapGen::CheckIfOnGrid()
{
	/*
	bOnGrid = true;

	for (int i = 0; i < CurrentBuildingTileArray.Num(); i++)
	{
		int findResult;
		if (findResult==INDEX_NONE)
		{
			bOnGrid = false;
		}	
	}
	*/
}

void AMapGen::SpawnBigBuilding(int typeOfBuilding)
{
	
	UWorld* const World = GetWorld();
	FActorSpawnParameters Params;
	Params.Owner = this->GetOwner();

	FVector* buildingPos;
	FRotator* buildingRotation;
	switch (typeOfBuilding)
	{
	default:
		break;
	case 1:
	{
		buildingPos = new FVector(currentTile->X*positionBase + positionBase / 2, currentTile->Y*positionBase + positionBase / 2, 0.0f);
		buildingRotation = ReturnRotator(typeOfBuilding);

		ATile_8_8* SpawnedBuilding_8_8 = World->SpawnActor<ATile_8_8>(Building_8_8, *buildingPos, *buildingRotation, Params);
		
		int buildingMesh = SpawnedBuilding_8_8->SelectBuildingModel();
		SpawnedBuilding_8_8->SetActorScale3D(FVector(35.0f, 35.0f, 35.0f));
		SpawnedBuilding_8_8->SetMyCoordinate(0, CurrentBuildingTileArray);

		SpawnedBuilding_8_8->BuildingType = EBuildingType::BUILDING_8x8;
		SpawnedBuilding_8_8->_buildingMesh = buildingMesh;
		SpawnedBuilding_8_8->rotator = *buildingRotation;
		
		MapAssets.Add(SpawnedBuilding_8_8);
	}
	break;

	case 2:
	{
		buildingPos = new FVector(currentTile->X*positionBase + positionBase / 2, currentTile->Y*positionBase + positionBase / 2 + positionBase, 0.0f);
		buildingRotation = ReturnRotator(typeOfBuilding);

		ATile_16_8* SpawnedBuilding_16_8 = World->SpawnActor<ATile_16_8>(Building_16_8, *buildingPos, *buildingRotation, Params);
		
		int buildingMesh = SpawnedBuilding_16_8->SelectBuildingModel();
		SpawnedBuilding_16_8->SetActorScale3D(FVector(35.0f, 35.0f, 35.0f));
		SpawnedBuilding_16_8->SetMyCoordinate(0, CurrentBuildingTileArray);

		SpawnedBuilding_16_8->BuildingType = EBuildingType::BUILDING_16x8;
		SpawnedBuilding_16_8->_buildingMesh = buildingMesh;
		SpawnedBuilding_16_8->rotator = *buildingRotation;

		MapAssets.Add(SpawnedBuilding_16_8);
	}
	break;

	case 3:
	{
		buildingPos = new FVector(currentTile->X*positionBase + positionBase / 2 + positionBase, currentTile->Y*positionBase + positionBase / 2, 0.0f);
		buildingRotation = ReturnRotator(typeOfBuilding);

		ATile_16_8* SpawnedBuilding_8_16 = World->SpawnActor<ATile_16_8>(Building_16_8, *buildingPos, *buildingRotation, Params);

		int buildingMesh = SpawnedBuilding_8_16->SelectBuildingModel();
		SpawnedBuilding_8_16->SetActorScale3D(FVector(35.0f, 35.0f, 35.0f));
		SpawnedBuilding_8_16->SetMyCoordinate(0, CurrentBuildingTileArray);

		SpawnedBuilding_8_16->BuildingType = EBuildingType::BUILDING_16x8;
		SpawnedBuilding_8_16->_buildingMesh = buildingMesh;
		SpawnedBuilding_8_16->rotator = *buildingRotation;

		MapAssets.Add(SpawnedBuilding_8_16);
	}
	break;
	}
	


}

FRotator* AMapGen::ReturnRotator(int _typeOfBuilding)
{
	if (_typeOfBuilding == 1)
	{
		int randomRotation = FMath::RandRange(1, 3);

		switch (randomRotation)
		{
		case 1:
			return new FRotator(0.f, 90.f, 0.f);
			break;
		case 2:
			return new FRotator(0.f, -90.f, 0.f);
			break;
		case 3:
			return new FRotator(0.f, 180.f, 0.f);
			break;
		}
	}
	if (_typeOfBuilding == 2)
	{
		int randomRotation = FMath::RandRange(1, 2);

		switch (randomRotation)
		{
		case 1:
			return new FRotator(0.f, 0.f, 0.f);
			break;
		case 2:
			return new FRotator(0.f, -180.f, 0.f);
			break;
		}
	}
	if (_typeOfBuilding == 3)
	{
		int randomRotation = FMath::RandRange(1, 2);

		switch (randomRotation)
		{
		case 1:
			return new FRotator(0.f, 90.f, 0.f);
			break;
		case 2:
			return new FRotator(0.f, -90.f, 0.f);
			break;
		}
	}
	return new FRotator(0.f, 0.f, 0.f);
	//else
	//{
	//	return new FRotator(0.f, 0.f, 0.f);
	//}
	//return new FRotator(0.f, 0.f, 0.f);
}

void AMapGen::AddBuildingBorder(int _typeOfBuilding)
{
	TArray<FVector2D*> borderVectors;

	switch (_typeOfBuilding)
	{
	case 0:
		break;
		//8x8 Selected
	case 1:
		borderVectors = Vectors_8_8_Border;
		break;
		//16x8 Vertical Selected
	case 2:
		borderVectors = Vectors_16_8_Vertical_Border;
		break;
		//16x8 Horizontal Selected
	case 3:
		borderVectors = Vectors_16_8_Horizontal_Border;
		break;
	default:
		break;
	}

	for (int i = 0; i < borderVectors.Num(); i++)
	{
		OccupiedBordersArray.Add(new FVector2D(borderVectors[i]->X+currentTile->X, borderVectors[i]->Y + currentTile->Y));
	}
}

void AMapGen::AddOccupiedTile()
{
	for (int i = 0; i < CurrentBuildingTileArray.Num(); i++)
	{
		OccupiedTileArray.Add(CurrentBuildingTileArray[i]);
	}
}

TArray<FVector2D> AMapGen::ReturnBorderTiles()
{
	TArray<FVector2D> _returnArray;
	for (size_t i = 0; i < OccupiedBordersArray.Num(); i++)
	{
		_returnArray.Add(*OccupiedBordersArray[i]);
	}
	
	return _returnArray;
}

TArray<FVector2D> AMapGen::ReturnOccupiedTiles()
{
	TArray<FVector2D> _returnArray;
	for (size_t i = 0; i < OccupiedTileArray.Num(); i++)
	{
		_returnArray.Add(*OccupiedTileArray[i]);
	}

	return _returnArray;
}

TArray<FVector2D> AMapGen::Return2DGrid()
{
	TArray<FVector2D> _returnArray;
	for (size_t i = 0; i < MapGrid.Num(); i++)
	{
		_returnArray.Add(*MapGrid[i]);
	}

	return _returnArray;
}

TArray<ATile*> AMapGen::ReturnMapAssets()
{
	return MapAssets;
}

void AMapGen::CreateRoadGenerator()
{
	UWorld* const World = GetWorld();

	FActorSpawnParameters Params;
	Params.Owner = this->GetOwner();

	FVector* position = new FVector(0.f,0.f,0.f);
	FRotator* rotation = new FRotator(0.f,0.f,0.f);

	RoadGenerator = World->SpawnActor<ARoadGen>(Road_Generator, *position, *rotation, Params);

	RoadGenerator->LoadAssets(MapGrid, OccupiedTileArray, OccupiedBordersArray);
}

//Reset the Map data
void AMapGen::CleanMap()
{
	if (RoadGenerator != NULL)
		RoadGenerator->EmptyAssets();

	MapGrid.Empty();
	OccupiedTileArray.Empty();
	OccupiedBordersArray.Empty();
	if (MapAssets.Num() != 0)
	{
		for (int i = 0; i < MapAssets.Num(); i++)
		{
			MapAssets[i]->Destroy();
		}
	}
	MapAssets.Empty();
	if (RoadGenerator != NULL)
		RoadGenerator->Destroy();
}

void AMapGen::SelectDensity(int _densityMultiplier)
{
	int MaxNmbOfBuildings = 0;
	//boolean to detect the minimum size to place 8x8 buildings
	bool b8x8;
	//boolean to detect the minimum size to place 16x8 buildings
	bool b16x8;

	//8x8 Can be placed
	if (gridX >= 2 && gridY >= 2)
		b8x8 = true;
	//16x8 Can be placed
	if (gridX >=4 && gridY>=2|| gridY >= 4 && gridX>=2)
		b16x8 = true;

	if (b8x8)
	{

		int x = (int)(gridX - (int)(gridX / 3))/2;
		int y = (int)(gridY - (int)(gridY / 3)) / 2;
		int result = x * y;

		//There is a limit to nmb of buildings, 3 is the ammount you can start to add density
		if (result < 3)
			_densityMultiplier = 1;

		//Limits the maximum number of buildings based on the density input
		MaxNmbOfBuildings = FMath::Ceil(result/_densityMultiplier);
		MaxNmbOf8x8Buildings = MaxNmbOfBuildings;
	}

	if (b16x8)
	{
		//Ratio 2:1
		MaxNmbOf16x8Buildings = (int)MaxNmbOfBuildings / 2;
		//MaxNmbOf8x8Buildings = MaxNmbOfBuildings - MaxNmbOf16x8Buildings*2;
	}
	//Also change the chanceToPlaceBuilding based on the multiplier, high density means that buildings are more likely to be placed
	chanceToPlaceBuilding = (int)100 / _densityMultiplier;
}

int AMapGen::ReturnNmb8x8()
{
	return MaxNmbOf8x8Buildings;
}

int AMapGen::ReturnNmb16x8()
{
	return MaxNmbOf16x8Buildings;
}

void AMapGen::UIPlaceBuildings()
{
	CleanMap();

	//Generate the Map Grid Again
	GenerateGrid();

	//Sets the Max Nmb of building for each type
	NmbOf8x8Buildings = MaxNmbOf8x8Buildings;
	NmbOf16x8Buildings = MaxNmbOf16x8Buildings;

	AddBigBuildings();
}

void AMapGen::UIPlaceRoads()
{
	if (RoadGenerator != NULL)
	{
		RoadGenerator->EmptyAssets();
		RoadGenerator->Destroy();
	}

	CreateRoadGenerator();
	RoadGenerator->FillEmptySpaces();
	bReplacePark = true;
}

void AMapGen::UIPlaceParks()
{
	if (!bReplacePark)
	{
		if (RoadGenerator != NULL)
		{
			RoadGenerator->EmptyAssets();
			RoadGenerator->Destroy();
		}

		CreateRoadGenerator();
		RoadGenerator->FillEmptySpaces();
	}

	RoadGenerator->Clean_4_4();
	RoadGenerator->CleanArray();
	bReplacePark = false;
}

void AMapGen::UISetRoads()
{
	RoadGenerator->GenerateRoads();
}

void AMapGen::UISaveAssets(FString _mapName)
{
	TArray<ATile*> TempAssets = RoadGenerator->ReturnRoadAssets();

	for (int i = 0; i < TempAssets.Num(); i++)
	{
		MapAssets.Add(TempAssets[i]);
	}

	SaveData = MakeShareable(new FJsonObject());

	for (int i = 0; i < MapAssets.Num(); i++)
	{
		FString objectName = "Object " + FString::FromInt(i);
		FAssetInfo AssetInfo;
		AssetInfo.x = MapAssets[i]->myCoordinates[0]->X;
		AssetInfo.y = MapAssets[i]->myCoordinates[0]->Y;
		
		AssetInfo.TypeOfBuilding = MapAssets[i]->BuildingType;
		AssetInfo.rotatorX = MapAssets[i]->rotator.Roll;
		AssetInfo.rotatorY = MapAssets[i]->rotator.Pitch;
		AssetInfo.rotatorZ = MapAssets[i]->rotator.Yaw;

		if (AssetInfo.TypeOfBuilding == EBuildingType::BUILDING_8x8)
		{
			AssetInfo.buildingMesh = Cast<ATile_8_8>(MapAssets[i])->_buildingMesh;
			AssetInfo.roadType = -1;
		}
		if (AssetInfo.TypeOfBuilding == EBuildingType::BUILDING_16x8)
		{
			AssetInfo.buildingMesh = Cast<ATile_16_8>(MapAssets[i])->_buildingMesh;
			AssetInfo.roadType = -1;
		}
		if (AssetInfo.TypeOfBuilding == EBuildingType::ROAD || AssetInfo.TypeOfBuilding == EBuildingType::PARK)
		{
			AssetInfo.roadType = Cast<ATile_4_4>(MapAssets[i])->roadType;
			AssetInfo.buildingMesh = -1;
		}
		
		AssetInfoData.Add(AssetInfo);
	}

	SaveToFile(_mapName);
}

void AMapGen::SaveToFile(FString fileName)
{
	// Convert save game json object to string
	FString SaveGameStringData;
	FString SaveDirectory = FPaths::GameContentDir();
	FString AbsoluteFilePath = SaveDirectory + "MapData/" +  fileName + ".txt";

	TArray< TSharedPtr<FJsonObject> > ObjArray;

	TSharedPtr<FJsonObject> FinalJsonObject;

	TSharedRef< TJsonWriter<> > JsonWriter = TJsonWriterFactory<>::Create(&SaveGameStringData);
	JsonWriter->WriteArrayStart();

	for (int i = 0; i < AssetInfoData.Num(); i++)
	{
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("x", AssetInfoData[i].x);
		JsonWriter->WriteValue("y", AssetInfoData[i].y);
		JsonWriter->WriteValue("TypeOfBuilding", (int)AssetInfoData[i].TypeOfBuilding);
		JsonWriter->WriteValue("rotatorX", AssetInfoData[i].rotatorX);
		JsonWriter->WriteValue("rotatorY", AssetInfoData[i].rotatorY);
		JsonWriter->WriteValue("rotatorZ", AssetInfoData[i].rotatorZ);
		JsonWriter->WriteValue("buildingMesh", AssetInfoData[i].buildingMesh);
		JsonWriter->WriteValue("roadType", AssetInfoData[i].roadType);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteArrayEnd();
	JsonWriter->Close();
	FFileHelper::SaveStringToFile(*SaveGameStringData, *AbsoluteFilePath);
}

TArray<FString> AMapGen::UILoadMapAssets()
{
	FString directoryToSearch = FPaths::GameContentDir() + "MapData/";
	FString filesStartingWith = TEXT("");
	FString fileExtensions = TEXT("txt");

	TArray<FString> filesInDirectory = GetAllFilesInDirectory(directoryToSearch, true, filesStartingWith, fileExtensions);

	return filesInDirectory;
}

///////////////////////PROTOTYPE
/*
void AMapGen::UICreateMiniMap(FString _mapName)
{
	FString SaveDirectory = FPaths::GameContentDir();
	FString AbsoluteFilePath = SaveDirectory + "MapData/" + _mapName + ".txt";

	FString LevelData;
	TSharedRef<TJsonReader<>> JsonRead = TJsonReaderFactory<>::Create(LevelData);

	//Grabing Assets
	FFileHelper::LoadFileToString(LevelData, *AbsoluteFilePath);

	TArray<FAssetInfo> data;
	FJsonObjectConverter::JsonArrayStringToUStruct(LevelData, &data, 0, 0);


}
*/

void AMapGen::UILoadMap(FString mapName)
{
	FString SaveDirectory = FPaths::GameContentDir();
	FString AbsoluteFilePath = SaveDirectory + "MapData/" + mapName + ".txt";

	FString LevelData;
	TSharedRef<TJsonReader<>> JsonRead = TJsonReaderFactory<>::Create(LevelData);

	//Grabing Assets
	FFileHelper::LoadFileToString(LevelData, *AbsoluteFilePath);

	TArray<FAssetInfo> data;
	FJsonObjectConverter::JsonArrayStringToUStruct(LevelData, &data, 0, 0);

	SpawnAssetsFromLevel(data);
}

void AMapGen::SpawnAssetsFromLevel(TArray<FAssetInfo> _data)
{
	CleanMap();

	for (int i = 0; i < _data.Num(); i++)
	{
		FAssetInfo assetInfo = _data[i];
		
		UWorld* const World = GetWorld();
		FActorSpawnParameters Params;
		Params.Owner = this->GetOwner();
		float positionOffsetX;
		float positionOffsetY;

		TSubclassOf<ATile> SpawnedAsset;

		switch (assetInfo.TypeOfBuilding)
		{
		case EBuildingType::ROAD:
			SpawnedAsset = Road_4_4;
			positionOffsetX = 0;
			positionOffsetY = 0;
			break;
		case EBuildingType::BUILDING_8x8:
			SpawnedAsset = Building_8_8;
			positionOffsetX = positionBase / 2;
			positionOffsetY = positionBase / 2;
			break;
		case EBuildingType::BUILDING_16x8:
			SpawnedAsset = Building_16_8;
			if (assetInfo.rotatorX == 0.0f && assetInfo.rotatorY == 0.0f && (assetInfo.rotatorZ == -90.0f || assetInfo.rotatorZ == 90.0f))
			{
				positionOffsetX = positionBase / 2 + positionBase;
				positionOffsetY = positionBase / 2;
			}
			else
			{
				positionOffsetX = positionBase / 2;
				positionOffsetY = positionBase / 2 + positionBase;
			}
			break;
		case EBuildingType::PARK:
			SpawnedAsset = Road_4_4;
			positionOffsetX = 0;
			positionOffsetY = 0;
			break;
		}

		FVector* assetPos = new FVector(assetInfo.x*positionBase + positionOffsetX, assetInfo.y*positionBase + positionOffsetY, 0);
		FRotator* assetRotation = new FRotator(assetInfo.rotatorY, assetInfo.rotatorZ, assetInfo.rotatorX);
		
		ATile* Asset = World->SpawnActor<ATile>(SpawnedAsset, *assetPos, *assetRotation, Params);

		Asset->SetActorScale3D(FVector(35.0f, 35.0f, 35.0f));

		CurrentBuildingTileArray.Empty();
		CurrentBuildingTileArray.Add(new FVector2D(assetInfo.x, assetInfo.y));

		Asset->SetMyCoordinate((int)assetInfo.TypeOfBuilding, CurrentBuildingTileArray);
		Asset->BuildingType = assetInfo.TypeOfBuilding;
		
		switch (assetInfo.TypeOfBuilding)
		{
		case EBuildingType::ROAD:
			Cast<ATile_4_4>(Asset)->ChangeRoadType(assetInfo.roadType);
			break;
		case EBuildingType::BUILDING_8x8:
			Cast<ATile_8_8>(Asset)->BuildingMesh->SetStaticMesh(Cast<ATile_8_8>(Asset)->BuildingsMesh_8_8[assetInfo.buildingMesh]);
			break;
		case EBuildingType::BUILDING_16x8:
			Cast<ATile_16_8>(Asset)->BuildingMesh->SetStaticMesh(Cast<ATile_16_8>(Asset)->BuildingsMesh_16_8[assetInfo.buildingMesh]);
			break;
		case EBuildingType::PARK:
			Cast<ATile_4_4>(Asset)->SelectParkModel();
			break;
		}

		MapAssets.Add(Asset);

	}
}

void AMapGen::UIStartGame()
{
	UWorld* const World = GetWorld();

	FActorSpawnParameters Params;
	Params.Owner = this->GetOwner();

	FVector* position = new FVector(0.f, 0.f, 0.f);
	FRotator* rotation = new FRotator(0.f, 0.f, 0.f);

	GameController = World->SpawnActor<AGameController>(Game_Controller, *position, *rotation, Params);
	GameController->LoadGrid(gridX,gridY);
}


/**
Gets all the files in a given directory.
@param directory The full path of the directory we want to iterate over.
@param fullpath Whether the returned list should be the full file paths or just the filenames.
@param onlyFilesStartingWith Will only return filenames starting with this string. Also applies onlyFilesEndingWith if specified.
@param onlyFilesEndingWith Will only return filenames ending with this string (it looks at the extension as well!). Also applies onlyFilesStartingWith if specified.
@return A list of files (including the extension).
*/

TArray<FString> AMapGen::GetAllFilesInDirectory(const FString directory, const bool fullPath, const FString onlyFilesStartingWith, const FString onlyFilesWithExtension)
{
	// Get all files in directory
	TArray<FString> directoriesToSkip;
	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
	PlatformFile.IterateDirectory(*directory, Visitor);
	TArray<FString> files;

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{
		const FString filePath = TimestampIt.Key();
		const FString fileName = FPaths::GetCleanFilename(filePath);
		bool shouldAddFile = true;

		// Check if filename starts with required characters
		if (!onlyFilesStartingWith.IsEmpty())
		{
			const FString left = fileName.Left(onlyFilesStartingWith.Len());

			if (!(fileName.Left(onlyFilesStartingWith.Len()).Equals(onlyFilesStartingWith)))
				shouldAddFile = false;
		}

		// Check if file extension is required characters
		if (!onlyFilesWithExtension.IsEmpty())
		{
			if (!(FPaths::GetExtension(fileName, false).Equals(onlyFilesWithExtension, ESearchCase::IgnoreCase)))
				shouldAddFile = false;
		}

		// Add full path to results
		if (shouldAddFile)
		{
			files.Add(fullPath ? filePath : fileName);
		}
	}

	return files;
}