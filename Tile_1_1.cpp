// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "Tile_1_1.h"

ATile_1_1::ATile_1_1() : Super()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetObject"));
	WidgetComponent->AttachTo(Root);
	WidgetComponent->SetWidgetClass(WidgetClass);
	WidgetComponent->SetDrawSize(FVector2D(115.f, 115.f));
	WidgetComponent->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
}


