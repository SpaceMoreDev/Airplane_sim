// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineActor.h"
#include "Components/SplineComponent.h"


// Sets default values
ASplineActor::ASplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneRoot);
	
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	SplineComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

