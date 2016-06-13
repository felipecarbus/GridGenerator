// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATile::SetMyCoordinate(int _buildingType, TArray<FVector2D*> _coordinates)
{
	myCoordinates = _coordinates;
}

