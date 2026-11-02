// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateSinglecastConsole.h"
#include "Components/SceneComponent.h"
#include "DelegateSinglecastLight.h"

// Sets default values
ADelegateSinglecastConsole::ADelegateSinglecastConsole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
}

// Called when the game starts or when spawned
void ADelegateSinglecastConsole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADelegateSinglecastConsole::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    LightCommand.Unbind();

    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ADelegateSinglecastConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastConsole::SetLeverState(bool bActive)
{
	bLeverActive = bActive;

	UpdateLeverVisuals(bLeverActive);

	LightCommand.ExecuteIfBound(bLeverActive);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastConsole::ToggleLightConnection(ADelegateSinglecastLight* Light)
{
    if (!IsValid(Light))
    {
        return;
    }

    const bool bDisconnect = (ConnectedLight == Light);

    if (IsValid(ConnectedLight))
    {
        LightCommand.ExecuteIfBound(false);
        ConnectedLight->SetConnectionState(false);
    }

    if (bDisconnect)
    {
        LightCommand.Unbind();
        ConnectedLight = nullptr;
        return;
    }

    LightCommand.BindUObject(Light, &ADelegateSinglecastLight::SetLightState);

    ConnectedLight = Light;
    ConnectedLight->SetConnectionState(true);

    LightCommand.ExecuteIfBound(bLeverActive);
}