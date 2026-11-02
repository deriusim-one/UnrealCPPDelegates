// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateLevelDisplay.generated.h"

class ADelegateDimmer;
class USceneComponent;
class UWidgetComponent;


UCLASS()
class DELEGATESCOURSE_API ADelegateLevelDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateLevelDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> LevelWidget;

	UPROPERTY(EditInstanceOnly, Category = "Delegates")
	TObjectPtr<ADelegateDimmer> Dimmer = nullptr;

	UFUNCTION()
	void HandleLevelChanged(float NewLevel);

	UFUNCTION(BlueprintImplementableEvent, Category = "Display|Visual")
	void UpdateDisplayVisuals(float NewLevel);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
