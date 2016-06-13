// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "GeneratorSettings.h"


// Sets default values
AGeneratorSettings::AGeneratorSettings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeneratorSettings::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeneratorSettings::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

