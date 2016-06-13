// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EBuildingType : uint8
{
	ROAD 	UMETA(DisplayName = "Road"),
	BUILDING_8x8 	UMETA(DisplayName = "Building 8x8"),
	BUILDING_16x8 	UMETA(DisplayName = "Building 8x8"),
	PARK	UMETA(DisplayName = "Park"),
	TILE	UMETA(DIsplayName = "Tile")
};

UCLASS()
class GRIDGENERATOR_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	TArray<FVector2D*> myCoordinates;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetMyCoordinate(int _buildingType,TArray<FVector2D*> _coordinates);	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EBuildingType BuildingType;

	UPROPERTY()
	FRotator rotator;
};
