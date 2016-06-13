// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerCharacter.generated.h"

class AGameController;

UCLASS()
class GRIDGENERATOR_API APlayerCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* CharacterMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* CharacterMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int movement_range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int current_movement;

	AGameController* gameController;

	FVector2D* currentCoordinate;
	TArray<FVector2D*> grid;

	UFUNCTION(BlueprintCallable, Category = "Check Movement")
	void CheckMovementRange();

	void SetGameController(AGameController* _gameController);
	void SetGrid(TArray<FVector2D*> _grid);

};
