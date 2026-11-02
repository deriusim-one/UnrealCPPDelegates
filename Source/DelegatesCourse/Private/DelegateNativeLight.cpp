// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateNativeLight.h"

#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DelegateNativeButton.h"
#include "Engine/Engine.h"

// Sets default values
ADelegateNativeLight::ADelegateNativeLight()
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
void ADelegateNativeLight::BeginPlay()
{
	Super::BeginPlay();

    SetLightState(false);

    if (IsValid(Button))
    {
        StateChangedHandle = Button->OnStateChanged.AddUObject(this, &ADelegateNativeLight::SetLightState);

        StaticMessageHandle = Button->OnStateChanged.AddStatic(&ADelegateNativeLight::ShowStaticMessage);

        LambdaMessageHandle = Button->OnStateChanged.AddLambda(
            [](bool bActive)
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(
                        -1,
                        2.0f,
                        FColor::Yellow,
                        bActive
                        ? TEXT("AddLambda: pulsante attivo")
                        : TEXT("AddLambda: pulsante inattivo"));
                }
            });
    }
	
}

// Called every frame
void ADelegateNativeLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADelegateNativeLight::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (IsValid(Button))
    {
        if (StateChangedHandle.IsValid())
        {
            Button->OnStateChanged.Remove(StateChangedHandle);
        }

        if (StaticMessageHandle.IsValid())
        {
            Button->OnStateChanged.Remove(StaticMessageHandle);
        }

        if (LambdaMessageHandle.IsValid())
        {
            Button->OnStateChanged.Remove(LambdaMessageHandle);
        }
    }

    StateChangedHandle.Reset();
    StaticMessageHandle.Reset();
    LambdaMessageHandle.Reset();

    Super::EndPlay(EndPlayReason);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateNativeLight::SetLightState(bool bActive)
{
    PointLight->SetVisibility(bActive);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateNativeLight::ShowStaticMessage(bool bActive)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, bActive ? TEXT("AddStatic: pulsante attivo") : TEXT("AddStatic: pulsante inattivo"));
    }
}