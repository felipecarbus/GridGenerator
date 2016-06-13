// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "RoadGen.h"


// Sets default values
ARoadGen::ARoadGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set West Direction
	NWSEDirections.Add(FVector2D(-1,0));
	//Set North Direction
	NWSEDirections.Add(FVector2D(0, -1));
	//Set East Direction
	NWSEDirections.Add(FVector2D(1, 0));
	//Set South Direction
	NWSEDirections.Add(FVector2D(0, 1));

	Coordinates_8_Around.Add(new FVector2D(0,0));
	Coordinates_8_Around.Add(new FVector2D(-1,-1));
	Coordinates_8_Around.Add(new FVector2D(0,-1));
	Coordinates_8_Around.Add(new FVector2D(1,-1));
	Coordinates_8_Around.Add(new FVector2D(1, 0));
	Coordinates_8_Around.Add(new FVector2D(1, 1));
	Coordinates_8_Around.Add(new FVector2D(0, 1));
	Coordinates_8_Around.Add(new FVector2D(-1, 1));
	Coordinates_8_Around.Add(new FVector2D(-1, 0));


}

// Called when the game starts or when spawned
void ARoadGen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoadGen::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARoadGen::LoadAssets(TArray<FVector2D*> _2DGrid, TArray<FVector2D*> _OccupiedGridArray, TArray<FVector2D*> _BuildingBorderGridArray)
{
	Road2DGrid = _2DGrid;
	OccupiedGridArray = _OccupiedGridArray;
	BuildingBorderGridArray = _BuildingBorderGridArray;

}

void ARoadGen::GenerateFullRoadAssets()
{
	FillEmptySpaces();
	Clean_4_4();
	CleanArray();
	GenerateRoads();
}

void ARoadGen::FillEmptySpaces()
{
	for (int i = 0; i < Road2DGrid.Num(); i++)
	{
		bTileOccupied = false;

		Coordinates.Empty();

		currentTile = Road2DGrid[i];

		for (int j = 0; j < OccupiedGridArray.Num(); j++)
		{
			if (*currentTile == *OccupiedGridArray[j])
			{
				bTileOccupied = true;
				break;
			}
		}

		if (!bTileOccupied)
		{
			//Coordinate to send to the BP Object
			Coordinates.Add(currentTile);

			//Add the currentTile coordinate to the list of roads coordinates
			RoadArray.Add(currentTile);

			SpawnRoad();
		}
	}
}

void ARoadGen::SpawnRoad()
{
	UWorld* const World = GetWorld();

	FVector* buildingPos = new FVector(currentTile->X*positionBase, currentTile->Y*positionBase, 0.0f);
	FRotator* buildingRotation = new FRotator(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters Params;
	Params.Owner = this->GetOwner();

	ATile_4_4* SpawnedRoad = World->SpawnActor<ATile_4_4>(Road_4_4, *buildingPos, *buildingRotation, Params);
	SpawnedRoad->SetActorScale3D(FVector(35.0f, 35.0f, 35.0f));

	//Sets the coordinate of the BP object,
	SpawnedRoad->SetMyCoordinate(0, Coordinates);

	SpawnedRoad->rotator = *buildingRotation;

	//Adds the BP_4_4 to an array of tiles objects
	RoadAssets.Add(SpawnedRoad);
}

void ARoadGen::EmptyAssets()
{
	if (RoadAssets.Num() != 0)
	{
		for (int i = 0; i < RoadAssets.Num(); i++)
		{
			RoadAssets[i]->Destroy();
		}
	}
	RoadAssets.Empty();
}

TArray<ATile*> ARoadGen::ReturnRoadAssets()
{
	return RoadAssets;
}

void ARoadGen::Clean_4_4()
{
	for (int i = 0; i < RoadArray.Num(); i++)
	{
		currentRoad = RoadArray[i];

		bNorthAvaiable = false;
		bEastAvaiable= false;
		bWestAvaiable = false;
		bSouthAvaiable = false;

		directions.Empty();

		//Check Self
		bool bSelfAvailable = CheckIfSpotIsAvailable(*currentRoad);

		if (bSelfAvailable)
		{
			//West Check
			FVector2D WestTile = FVector2D(NWSEDirections[0].X + currentRoad->X, NWSEDirections[0].Y + currentRoad->Y);
			bool bWestAvaiable = CheckIfSpotIsAvailable(WestTile);
			//Adds the West direction to the possible directions array
			if (bWestAvaiable)
				directions.Add(3);

			//North Check
			FVector2D NorthTile = FVector2D(NWSEDirections[1].X + currentRoad->X, NWSEDirections[1].Y + currentRoad->Y);
			bool bNorthAvaiable = CheckIfSpotIsAvailable(NorthTile);
			//Adds the West direction to the possible directions array
			if (bNorthAvaiable)
				directions.Add(0);

			//East Check
			FVector2D EastTile = FVector2D(NWSEDirections[2].X + currentRoad->X, NWSEDirections[2].Y + currentRoad->Y);
			bool bEastAvaiable = CheckIfSpotIsAvailable(EastTile);
			//Adds the West direction to the possible directions array
			if (bEastAvaiable)
				directions.Add(1);

			//South Check
			FVector2D SouthTile = FVector2D(NWSEDirections[3].X + currentRoad->X, NWSEDirections[3].Y + currentRoad->Y);
			bool bSouthAvaiable = CheckIfSpotIsAvailable(SouthTile);
			//Adds the West direction to the possible directions array
			if (bSouthAvaiable)
				directions.Add(2);

			if (directions.Num() != 0)
			{
				int randomDir = directions[FMath::RandRange(0, directions.Num() - 1)];

				if (bNorthAvaiable || bWestAvaiable || bEastAvaiable || bSouthAvaiable)
					SpawnParks(randomDir);
			}
		}
	}
}

bool ARoadGen::CheckIfSpotIsAvailable(FVector2D tile)
{
	bool bIsOnGrid = false;

	for (int i = 0; i < Road2DGrid.Num(); i++)
	{
		if (tile == *Road2DGrid[i])
		{
			bIsOnGrid=true;
		}
	}

	//if the building is on the grid, proceed to check if it is on an occupied spot, else return false
	if (bIsOnGrid)
	{
		for (int i = 0; i < OccupiedGridArray.Num(); i++)
		{
			if (tile == *OccupiedGridArray[i])
			{
				//The Tile is occupying a tile where there is a building
				return false;
			}
		}
		for (int i = 0; i < BuildingBorderGridArray.Num(); i++)
		{
			if (tile == *BuildingBorderGridArray[i])
			{
				//The Tile is occupying a tile that is the border of a building
				return false;
			}
		}

		//If the tile is not within a occupied or border tile then it's possible to place it, so return true
		return true;
	}
	else
	{
		return false;
	}
}

void ARoadGen::SpawnParks(int _randomDir)
{
	currentPark = currentRoad;

	UWorld* const World = GetWorld();

	FRotator parkRotation;
	FVector parkPosition;

	FVector2D* nextPark;

	//Select the rotation and position of the park, N,W,S or E
	switch (_randomDir)
	{
	default:
		break;
	//North
	case 0:
		parkRotation = FRotator(0.f, 90.f, 0.f);
		parkPosition = FVector(currentRoad->X * positionBase,(currentRoad->Y-1)* positionBase,0.f);
		nextPark = new FVector2D(currentRoad->X, currentRoad->Y - 1);
		break;
	//East
	case 1:
		parkRotation = FRotator(0.f, 0.f, 0.f);
		parkPosition = FVector((currentRoad->X+1) * positionBase, currentRoad->Y* positionBase, 0.f);
		nextPark = new FVector2D(currentRoad->X+1, currentRoad->Y);
		break;
	//South
	case 2:
		parkRotation = FRotator(0.f, -90.f, 0.f);
		parkPosition = FVector(currentRoad->X * positionBase, (currentRoad->Y + 1)* positionBase, 0.f);
		nextPark = new FVector2D(currentRoad->X, currentRoad->Y + 1);
		break;
	//West
	case 3:
		parkRotation = FRotator(0.f, 0.f, 0.f);
		parkPosition = FVector((currentRoad->X - 1) * positionBase, currentRoad->Y* positionBase, 0.f);
		nextPark = new FVector2D(currentRoad->X-1, currentRoad->Y);
		break;
	}

	TArray<FVector2D*> nextParkArray =  TArray<FVector2D*>();
	nextParkArray.Add(nextPark);

	FActorSpawnParameters Params;
	Params.Owner = this->GetOwner();

	//Spawns the Second Park First
	ATile_4_4* SpawnedSecondPark = World->SpawnActor<ATile_4_4>(Road_4_4, parkPosition, parkRotation, Params);
	SpawnedSecondPark->SetActorScale3D(FVector(35.0f, 35.0f, 35.0f));

	//Sets the coordinate of the BP object,
	SpawnedSecondPark->SetMyCoordinate(0, nextParkArray);
	
	//Switch the mesh, to the park model
	SpawnedSecondPark->SelectParkModel();

	//Then spawns the First Park
	ATile_4_4* SpawnedFirstPark = World->SpawnActor<ATile_4_4>(Road_4_4, FVector(currentPark->X*positionBase,currentPark->Y*positionBase,0.f), parkRotation, Params);
	SpawnedFirstPark->SetActorScale3D(FVector(35.0f, 35.0f, 35.0f));

	TArray<FVector2D*> currentParkArray = TArray<FVector2D*>();
	currentParkArray.Add(currentPark);

	//Sets the coordinate of the BP object,
	SpawnedFirstPark->SetMyCoordinate(0, currentParkArray);
	
	//Switch the mesh, to the park model
	SpawnedFirstPark->SelectParkModel();

	AddOccupiedTilesAround(nextPark);
	AddOccupiedTilesAround(currentPark);

	CheckMapAssets(nextPark, SpawnedSecondPark);
	CheckMapAssets(currentPark, SpawnedFirstPark);

	RemoveFromRoadArray(nextPark);
	RemoveFromRoadArray(currentPark);

	//RoadAssets.Add(SpawnedSecondPark);
	//RoadAssets.Add(SpawnedFirstPark);

	SpawnedFirstPark->BuildingType = EBuildingType::PARK;
	SpawnedSecondPark->BuildingType = EBuildingType::PARK;

	SpawnedFirstPark->rotator = parkRotation;
	SpawnedSecondPark->rotator = parkRotation;
}

void ARoadGen::AddOccupiedTilesAround(FVector2D* _tile)
{
	OccupiedGridArray.Add(_tile);
	for (int i = 0; i < Coordinates_8_Around.Num(); i++)
	{
		BuildingBorderGridArray.Add(new FVector2D(_tile->X + Coordinates_8_Around[i]->X, _tile->Y + Coordinates_8_Around[i]->Y));
	}
}

//Destroy the physical objects in the scene
void ARoadGen::CheckMapAssets(FVector2D* _park, ATile* _parkTile)
{
	for (int i = 0; i < RoadAssets.Num(); i++)
	{
		ATile* selectedTile = RoadAssets[i];
		
		if (*(selectedTile->myCoordinates[0]) == *(_parkTile->myCoordinates[0]))
		{
			selectedTile->Destroy();
			RoadAssets[i] = _parkTile;
			return;
		}
	}
}

void ARoadGen::RemoveFromRoadArray(FVector2D* _tile)
{
	for (int i = 0; i < RoadArray.Num(); i++)
	{
		if (RoadArray[i]->X == _tile->X && RoadArray[i]->Y == _tile->Y)
	    {
			//RoadArray.Remove(RoadArray[i]);
			RoadArrayIndexToRemove.Add(_tile);
		}
	}
}

void ARoadGen::CleanArray()
{
	for (int i = 0; i < RoadArrayIndexToRemove.Num(); i++)
	{
		for (int j = 0; j < RoadArray.Num(); j++)
		{
			FVector2D vector = *(RoadArrayIndexToRemove[i]);
			if (vector.X == RoadArray[j]->X && vector.Y == RoadArray[j]->Y)
			{
				RoadArray.RemoveAt(j,true);
			}
		}

	}
}

void ARoadGen::GenerateRoads()
{
	for (int i = 0; i < RoadArray.Num(); i++)
	{
		FVector2D currentRoad = *(RoadArray[i]);
		FVector2D northRoad = FVector2D(currentRoad.X, currentRoad.Y - 1);
		FVector2D eastRoad = FVector2D(currentRoad.X + 1, currentRoad.Y);
		FVector2D southRoad = FVector2D(currentRoad.X, currentRoad.Y+1);
		FVector2D westRoad = FVector2D(currentRoad.X - 1, currentRoad.Y);

		bool bNorthAvailable = CheckIfOnGrid(northRoad);
		bool bEastAvailable = CheckIfOnGrid(eastRoad);
		bool bSouthAvailable = CheckIfOnGrid(southRoad);
		bool bWestAvailable = CheckIfOnGrid(westRoad);

		//4 Directions Road Section 
		if (bNorthAvailable && bEastAvailable && bSouthAvailable && bWestAvailable)
		{
			ChangeRoad(currentRoad, 2);
			continue;
		}

		//3 Directions Road Section NES
		if (bNorthAvailable && bEastAvailable && bSouthAvailable)
		{
			ChangeRoad(currentRoad, 7);
			continue;
		}

		//3 Directions Road Section ESW
		if ( bEastAvailable && bSouthAvailable && bWestAvailable)
		{
			ChangeRoad(currentRoad, 8);
			continue;
		}

		//3 Directions Road Section SWN
		if (bSouthAvailable && bWestAvailable && bNorthAvailable)
		{
			ChangeRoad(currentRoad, 9);
			continue;
		}
		//3 Directions Road Section WNE
		if (bWestAvailable && bNorthAvailable && bEastAvailable)
		{
			ChangeRoad(currentRoad, 10);
			continue;
		}
		//2 Directions Road Section NS
		if (bNorthAvailable && bSouthAvailable)
		{
			ChangeRoad(currentRoad, 0);
			continue;
		}
		//2 Directions Road Section NE
		if (bNorthAvailable && bEastAvailable)
		{
			ChangeRoad(currentRoad, 3);
			continue;
		}
		//2 Directions Road Section ES
		if (bSouthAvailable && bEastAvailable)
		{
			ChangeRoad(currentRoad, 4);
			continue;
		}
		//2 Directions Road Section SW
		if (bSouthAvailable && bWestAvailable)
		{
			ChangeRoad(currentRoad, 5);
			continue;
		}
		//2 Directions Road Section WN
		if (bNorthAvailable && bWestAvailable)
		{
			ChangeRoad(currentRoad, 6);
			continue;
		}
		//1 Direction Road Section North or South
		if (bNorthAvailable || bSouthAvailable)
		{
			ChangeRoad(currentRoad, 0);
			continue;
		}

		if (bWestAvailable || bEastAvailable)
		{
			ChangeRoad(currentRoad, 1);
			continue;
		}

	}
}

bool ARoadGen::CheckIfOnGrid(FVector2D tile)
{

	bool bOnGrid = false;
	//Check if the spot is inside the grid
	for (int i = 0; i < Road2DGrid.Num(); i++)
	{
		if (tile == *Road2DGrid[i])
		{
			bOnGrid = true;
		}
	}

	//if the building is on the grid, proceed to check if it is on an occupied spot, else return false
	if (bOnGrid)
	{
		for (int i = 0; i < OccupiedGridArray.Num(); i++)
		{
			if (tile == *OccupiedGridArray[i])
			{
				//The Tile is occupying a tile where there is a building or park
				return false;
			}
		}
		//Not occupying any building or park tiles
		return true;
	}
	else
	{
		//Out of the grid, so not available
		return false;
	}
}

void ARoadGen::ChangeRoad(FVector2D coordinate, int roadType)
{
	for (int i = 0; i < RoadAssets.Num(); i++)
	{
		ATile_4_4* road = Cast<ATile_4_4>(RoadAssets[i]);
		if (*(road->myCoordinates[0]) == coordinate)
		{
			road->ChangeRoadType(roadType);
			road->BuildingType = EBuildingType::ROAD;
		}
	}
}

TArray<FVector2D> ARoadGen::ReturnOccupiedTiles()
{
	TArray<FVector2D> _returnArray;
	for (size_t i = 0; i < OccupiedGridArray.Num(); i++)
	{
		_returnArray.Add(*OccupiedGridArray[i]);
	}

	return _returnArray;
}

TArray<FVector2D> ARoadGen::ReturnRoadArray()
{
	TArray<FVector2D> _returnArray;
	for (size_t i = 0; i < RoadArray.Num(); i++)
	{
		_returnArray.Add(*RoadArray[i]);
	}

	return _returnArray;
}

void ARoadGen::SetRoadAssets(TArray<ATile*> _roadAssets)
{
	for (int i = 0; i < _roadAssets.Num(); i++)
	{
		currentTile= _roadAssets[i]->myCoordinates[0];
		SpawnRoad();
	}
}