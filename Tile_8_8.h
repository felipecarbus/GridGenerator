// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "Tile_8_8.generated.h"

/**
 * 
 */
UCLASS()
class GRIDGENERATOR_API ATile_8_8 : public ATile
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BuildingModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	TArray<UStaticMesh*> BuildingsMesh_8_8;

	UFUNCTION(BlueprintCallable, Category = "Return Arrays")
	TArray<FVector2D> ReturnCoordinates();

	//////////////////////////////////////////////////////////////////////////
	// Constructor
	ATile_8_8();

	int SelectBuildingModel();

	int _buildingMesh;

};
