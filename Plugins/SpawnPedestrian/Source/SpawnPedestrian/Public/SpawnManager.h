#pragma once

#include "SimpleNode.h"

class SPAWNPEDESTRIAN_API FSpawnManager
{
public:
	FSpawnManager();

	void InitializeNavMesh();
	void InitializePedestrian();

	// UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyOwnCategory")
	void SpawnPedestrian(FVector StartLocation, FVector EndLocation) const;

protected:
	static void DummySpawnBoxedVolume(FVector Origin, FVector BoxExtend, TCHAR* VolumeClassName);

	
private:
	// Store the blueprint pedestrian character, need to be initialized in the constructor
	UBlueprint* PedestrianCharacterBP;

	// Store A list of possible moveable points.
	TArray<FVector> SideWalkCenters;
};