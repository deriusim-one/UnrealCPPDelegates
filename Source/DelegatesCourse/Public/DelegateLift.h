// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateLift.generated.h"

class USceneComponent;
class UStaticMeshComponent;


UCLASS()
class DELEGATESCOURSE_API ADelegateLift : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateLift();

	bool CanMoveToFloor(int32 TargetFloor) const;

	void MoveToFloor(int32 TargetFloor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> PlatformPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift", meta = (ClampMin = "1.0"))
	float UpperFloorHeight = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift", meta = (ClampMin = "0.1"))
	float TravelDuration = 3.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Lift|State")
	int32 CurrentFloor = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Lift|State")
	bool bIsMoving = false;

	int32 DestinationFloor = 0;
	float TravelElapsedTime = 0.0f;

	FVector GroundFloorLocation = FVector::ZeroVector;
	FVector MovementStartLocation = FVector::ZeroVector;
	FVector MovementTargetLocation = FVector::ZeroVector;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
