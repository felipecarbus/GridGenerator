// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "Tile_8_8.h"

ATile_8_8::ATile_8_8() : Super()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->AttachTo(Root);
}

TArray<FVector2D> ATile_8_8::ReturnCoordinates()
{
	TArray<FVector2D> _returnArray;
	for (size_t i = 0; i < myCoordinates.Num(); i++)
	{
		_returnArray.Add(*myCoordinates[i]);
	}

	return _returnArray;
}

int ATile_8_8::SelectBuildingModel()
{
	int arrayElement= FMath::RandRange(0, BuildingsMesh_8_8.Num() - 1);
	BuildingMesh->SetStaticMesh(BuildingsMesh_8_8[arrayElement]);
	return arrayElement;
}


