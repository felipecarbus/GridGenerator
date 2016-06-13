// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "Tile_4_4.h"

ATile_4_4::ATile_4_4() : Super()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->AttachTo(Root);
	BuildingMesh->SetStaticMesh(BuildingModel);

	roadType = -1;
}

TArray<FVector2D> ATile_4_4::ReturnCoordinates()
{
	TArray<FVector2D> _returnArray;
	for (size_t i = 0; i < myCoordinates.Num(); i++)
	{
		_returnArray.Add(*myCoordinates[i]);
	}

	return _returnArray;
}

void ATile_4_4::SelectParkModel()
{
	BuildingMesh->SetStaticMesh(ParkModel);
}

void ATile_4_4::ChangeRoadType(int _roadType)
{
	BuildingMesh->SetStaticMesh(RoadMeshes[_roadType]);
	roadType = _roadType;
}

