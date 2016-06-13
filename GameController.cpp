// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "GameController.h"


// Sets default values
AGameController::AGameController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGameController::LoadGrid(int _grid_X, int _grid_Y)
{
	grid_X = _grid_X * 4;
	grid_Y = _grid_Y * 4;

	for (int i = 0; i < grid_X; i++)
	{
		for (int j = 0; j < grid_Y; j++)
		{
			Grid.Add(new FVector2D(i, j));
		}
	}

	SpawnTiles();
	SpawnPlayerCharacter();

}

void AGameController::SpawnTiles()
{
	UWorld* const World = GetWorld();

	FActorSpawnParameters Params;
	Params.Owner = this->GetOwner();

	for (int i = 0; i < Grid.Num(); i++)
	{
		FVector* position = new FVector(Grid[i]->X - 184 + 123 * Grid[i]->X , Grid[i]->Y - 184 + 123 * Grid[i]->Y, -45.f);
		FRotator* rotation = new FRotator(0.f, 0.f, 0.f);

		ATile_1_1* Tile = World->SpawnActor<ATile_1_1>(Tile_BP, *position, *rotation, Params);
		TArray<FVector2D*> Coordinates = TArray<FVector2D*>();
		Coordinates.Add(new FVector2D(Grid[i]->X, Grid[i]->Y));
		Tile->SetMyCoordinate(5, Coordinates);
		Tiles.Add(Tile);
	}

}

void AGameController::SpawnPlayerCharacter()
{
	UWorld* const World = GetWorld();

	FActorSpawnParameters Params;
	Params.Owner = this->GetOwner();

	FVector* position = new FVector(-180.f, -190.f, -45.f);
	FRotator* rotation = new FRotator(0.f, 0.f, 0.f);

	PlayerCharacter = World->SpawnActor<APlayerCharacter>(Player_Character, *position, *rotation, Params);
	PlayerCharacter->SetActorScale3D(FVector(0.7f, 0.7f, 0.7f));
	PlayerCharacter->currentCoordinate = new FVector2D(0.0f, 0.0f);
	PlayerCharacter->SetGameController(this);
	PlayerCharacter->SetGrid(Grid);
}

void AGameController::HighLightPath(TArray<FVector2D*> _tilesCoordinates)
{

	for (int i = 0; i < Tiles.Num(); i++)
	{
		for (int j = 0; j < _tilesCoordinates.Num(); j++)
		{
			if (Tiles[i]->myCoordinates[0]->X == _tilesCoordinates[j]->X && Tiles[i]->myCoordinates[0]->Y == _tilesCoordinates[j]->Y)
			{
				Tiles[i]->ChangeTileToAvailable();
			}
		}
	}
}
