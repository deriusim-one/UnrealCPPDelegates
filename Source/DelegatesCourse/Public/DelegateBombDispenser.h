// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateBombDispenser.generated.h"

class ADelegateBombSpawner;
class UBoxComponent;
class UPrimitiveComponent;
class USceneComponent;
class UStaticMeshComponent;

DECLARE_DELEGATE_RetVal(bool, FCanSpawnBombSignature);


UCLASS()
class DELEGATESCOURSE_API ADelegateBombDispenser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateBombDispenser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ActivationBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bomb")
	TObjectPtr<ADelegateBombSpawner> BombSpawner = nullptr;

	FCanSpawnBombSignature CanSpawnBombDelegate;

	UFUNCTION(BlueprintImplementableEvent, Category = "Button|Visual")
	void UpdateButtonVisuals(bool bActive);

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
