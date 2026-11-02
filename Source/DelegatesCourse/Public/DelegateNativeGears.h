// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateNativeGears.generated.h"

class ADelegateNativeButton;
class USceneComponent;
class UStaticMeshComponent;


UCLASS()
class DELEGATESCOURSE_API ADelegateNativeGears : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateNativeGears();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USceneComponent> SceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> Gear1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> Gear2;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> Gear3;

    UPROPERTY(EditInstanceOnly, Category = "Delegates")
    TObjectPtr<ADelegateNativeButton> PressurePlate = nullptr;

    FDelegateHandle StateChangedHandle;

    bool bIsRunning = false;
    float RotationSpeed = 80.0f;

    void SetGearsState(bool bActive);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
