// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "Tile_4_4.generated.h"

/**
 * 
 */
UCLASS()
class GRIDGENERATOR_API ATile_4_4 : public ATile
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BuildingModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ParkModel;

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<FVector2D> ReturnCoordinates();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> RoadMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int roadType;

	//////////////////////////////////////////////////////////////////////////
	// Constructor
	ATile_4_4();

	void SelectParkModel();
	void ChangeRoadType(int _roadType);
};
