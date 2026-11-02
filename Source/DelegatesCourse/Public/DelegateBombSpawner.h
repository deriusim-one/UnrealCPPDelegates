// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateBombSpawner.generated.h"

class USceneComponent;


UCLASS()
class DELEGATESCOURSE_API ADelegateBombSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateBombSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bomb")
	TSubclassOf<AActor> BombClass;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Bomb")
	TObjectPtr<AActor> ActiveBomb = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CanSpawnBomb() const;

	void SpawnBomb();
};
