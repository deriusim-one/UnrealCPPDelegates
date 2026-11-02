// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateSinglecastConsole.generated.h"

class USceneComponent;
class ADelegateSinglecastLight;

DECLARE_DELEGATE_OneParam(FSinglecastLightCommandSignature, bool);


UCLASS()
class DELEGATESCOURSE_API ADelegateSinglecastConsole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateSinglecastConsole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FSinglecastLightCommandSignature LightCommand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Lights")
	TObjectPtr<ADelegateSinglecastLight> LightA = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Lights")
	TObjectPtr<ADelegateSinglecastLight> LightB = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "State")
	TObjectPtr<ADelegateSinglecastLight> ConnectedLight = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "State")
	bool bLeverActive = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Console|Visual")
	void UpdateLeverVisuals(bool bActive);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Console")
	void SetLeverState(bool bActive);

	UFUNCTION(BlueprintCallable, Category = "Console")
	void ToggleLightConnection(ADelegateSinglecastLight* Light);
};
