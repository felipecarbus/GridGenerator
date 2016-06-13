// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Tile_1_1.generated.h"

/**
 * 
 */
UCLASS()
class GRIDGENERATOR_API ATile_1_1 : public ATile
{
	GENERATED_BODY()

	int availableSpot;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetClassAvailable;

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeTileToAvailable();

	//////////////////////////////////////////////////////////////////////////
	// Constructor
	ATile_1_1();
};
