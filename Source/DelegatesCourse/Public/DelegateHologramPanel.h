// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateHologramPanel.generated.h"

class UBoxComponent;
class UPrimitiveComponent;
class USceneComponent;
class UStaticMesh;
class UStaticMeshComponent;

// ESERCIZIO_BEGIN: signature
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHologramChangedSignature, UStaticMesh*, NewMesh, FLinearColor, NewColor);
// ESERCIZIO_END


UCLASS()
class DELEGATESCOURSE_API ADelegateHologramPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateHologramPanel();

	// ESERCIZIO_BEGIN: proprieta del delegate
	UPROPERTY(BlueprintAssignable, Category = "Hologram|Events")
	FHologramChangedSignature OnHologramChanged;
	// ESERCIZIO_END

	UFUNCTION(BlueprintCallable, Category = "Hologram")
	void NextShape();

	UFUNCTION(BlueprintCallable, Category = "Hologram")
	void NextColor();

	UFUNCTION(BlueprintPure, Category = "Hologram")
	UStaticMesh* GetCurrentMesh() const;

	UFUNCTION(BlueprintPure, Category = "Hologram")
	FLinearColor GetCurrentColor() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ShapeButtonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ColorButtonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ShapeButtonBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ColorButtonBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hologram")
	TArray<TObjectPtr<UStaticMesh>> AvailableMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hologram")
	TArray<FLinearColor> AvailableColors = {FLinearColor::Red, FLinearColor::Blue, FLinearColor::Green};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hologram")
	int32 CurrentShapeIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hologram")
	int32 CurrentColorIndex = 0;

	UFUNCTION(BlueprintImplementableEvent, Category = "Hologram")
	void UpdateButtonVisuals(UStaticMeshComponent* ButtonMesh, bool bPressed);

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	void NotifyHologramChanged();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
