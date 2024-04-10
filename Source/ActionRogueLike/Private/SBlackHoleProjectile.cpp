// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHoleProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	Speed = 250;
	ProjectileMovement->InitialSpeed=Speed;
	UseRange = true;
	Range = 1000;
	SphereComp -> SetCollisionResponseToAllChannels(ECR_Overlap);

}

void ASBlackHoleProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Pull();
}

void ASBlackHoleProjectile::OnDissapate()
{
	if(ParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(), // World context
		ParticleSystem, // Your particle system template
		GetActorLocation(), // World location where the emitter should spawn
		FRotator::ZeroRotator, // Initial rotation
		true // Whether to auto-destroy the emitter when it's done
		);
	}
	Destroy();
}

void ASBlackHoleProjectile::OnOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap)
{
	if(OtherActor != GetInstigator())
	{
		if(OtherComponent->GetCollisionObjectType()==ECC_PhysicsBody)
		{
					OtherActor->Destroy();
		}
	}
}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	//SphereComp -> SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Ignore);
}

void ASBlackHoleProjectile::Pull()
{
	TArray<FHitResult>Hits;
	FCollisionObjectQueryParams Params;
	//Params.AddObjectTypesToQuery(ECC_WorldDynamic);
	//Params.AddObjectTypesToQuery(ECC_WorldStatic);
	Params.AddObjectTypesToQuery(ECC_PhysicsBody);
	FCollisionShape sphere;
	sphere.SetSphere(Radius);
	GetWorld()->SweepMultiByObjectType(Hits,GetActorLocation(),GetActorLocation(),FQuat::Identity,Params,sphere);
	for(FHitResult hit: Hits)
	{
		AActor* hitActor = hit.GetActor();
		AActor* InstActor = Cast<AActor>(GetInstigator());
		if(hitActor && InstActor)
		{
			if(hitActor != InstActor)
			{
				FVector blastDirection = UKismetMathLibrary::FindLookAtRotation(hitActor->GetActorLocation(),GetActorLocation()).Vector();
				hitActor->FindComponentByClass<UPrimitiveComponent>()->AddImpulse(blastDirection*Power);
			}
		}
	}
}
