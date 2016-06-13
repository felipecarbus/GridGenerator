// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "GameController.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CharacterMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMeshComponent"));
	CharacterMeshComponent->AttachTo(Root);
	CharacterMeshComponent->SetSkeletalMesh(CharacterMesh);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APlayerCharacter::CheckMovementRange()
{
	//int lowerRange = movement_range;
	//int maxRange = currentCoordinate->X + currentCoordinate->Y + movement_range;

	TArray<FVector2D*> coordinatesAvailable;

	for (int i = 0; i < grid.Num(); i++)
	{
		int sum = FMath::Abs((grid[i]->X - currentCoordinate->X) + (grid[i]->Y - currentCoordinate->Y));
		//int sum = FMath::Abs(grid[i]->X + grid[i]->Y);
		if (sum < movement_range)
		{
			coordinatesAvailable.Add(grid[i]);
		}
	}
	gameController->HighLightPath(coordinatesAvailable);
}

void APlayerCharacter::SetGameController(AGameController* _gameController)
{
	gameController = _gameController;
}

void APlayerCharacter::SetGrid(TArray<FVector2D*> _grid)
{
	grid = _grid;
}
