// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePawn.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

ASplinePawn::ASplinePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Spline->SetupAttachment(RootComponent);
}

void ASplinePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASplinePawn::Tick(float DeltaTime)
{
}

void ASplinePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}
