// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateHologramDisplay.generated.h"

class ADelegateHologramPanel;
class USceneComponent;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class DELEGATESCOURSE_API ADelegateHologramDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateHologramDisplay();

	UFUNCTION(BlueprintCallable, Category = "Hologram")
	void ApplyHologramSettings(UStaticMesh* NewMesh, FLinearColor NewColor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> HologramMesh;

	UFUNCTION(BlueprintImplementableEvent, Category = "Hologram")
	void UpdateHologramVisuals(UStaticMesh* NewMesh, FLinearColor NewColor);

	UPROPERTY(EditInstanceOnly, Category = "Hologram")
	TObjectPtr<ADelegateHologramPanel> HologramPanel = nullptr;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
