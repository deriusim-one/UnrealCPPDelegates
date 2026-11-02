// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateSinglecastLamp.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DelegateSinglecastButton.h"

// Sets default values
ADelegateSinglecastLamp::ADelegateSinglecastLamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
    LightMesh->SetupAttachment(SceneRoot);

    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(SceneRoot);
    PointLight->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void ADelegateSinglecastLamp::BeginPlay()
{
	Super::BeginPlay();
	
    SetLightState(false);

    if (IsValid(Button))
    {
        FDynamicButtonCommandSignature LightCommand;

        LightCommand.BindDynamic(this, &ADelegateSinglecastLamp::SetLightState);

        Button->SetCommand(LightCommand);
    }
}

// Called every frame
void ADelegateSinglecastLamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastLamp::SetLightState_Implementation(bool bActive)
{
    PointLight->SetVisibility(bActive);
}