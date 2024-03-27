// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "SGamePlayInterface.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USInteractionComponent::PrimaryInteract()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Called:2"));
	
	//Get object type
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);


	//Get origin of Line from Actor
	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation; 
	MyOwner ->GetActorEyesViewPoint(EyeLocation,EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector()* 200);

	//Test if Hit
	//FHitResult Hit;
	//bool lineHit = GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,ObjectQueryParams);
	float radius = 50;
	FCollisionShape Shape;
	Shape.SetSphere(radius);
	
	TArray<FHitResult> Hits;	
	bool lineHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End,FQuat::Identity,ObjectQueryParams,Shape);
			FColor lineColor = lineHit? FColor::Green : FColor::Red;

	for(FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
			if(HitActor)
        	{
        		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Called:1"));
        		if(HitActor->Implements<USGamePlayInterface>())
        		{
        			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Called:0"));
        			APawn* MyPawn = Cast<APawn>(MyOwner);
        			ISGamePlayInterface::Execute_Interact(HitActor,MyPawn);
        			break;
        		}
        	}
		DrawDebugSphere(GetWorld(),Hit.ImpactPoint,radius,32,lineColor,false,2.0f);
	}
	
			DrawDebugLine(GetWorld(),EyeLocation,End,lineColor,false,2.0f,0.0f,2.0f);

}