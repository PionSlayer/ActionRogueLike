// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh -> SetupAttachment(BaseMesh);

	pitch = 80;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(pitch,0,0));
}

void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

