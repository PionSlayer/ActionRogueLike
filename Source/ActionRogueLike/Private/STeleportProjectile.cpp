// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	hit = false;
}

void ASTeleportProjectile::OnDissapate() 
{
	StartTeleportCountDown();
}
void ASTeleportProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(GetInstigator() != OtherActor)
	{
		DrawDebugString(GetWorld(),SphereComp->GetComponentLocation(),"HELLO",this,FColor::Green,5,false,2);
		StartTeleportCountDown();
	}
}
void ASTeleportProjectile::StartTeleportCountDown()
{
	if(!hit)
	{
		hit=true;
		ProjectileMovement->SetVelocityInLocalSpace(FVector::Zero());
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
		GetWorldTimerManager().SetTimer(TeleportDelay,this,&ASTeleportProjectile::Teleport,Delay);
	}
}
void ASTeleportProjectile::Teleport()
{
	GetInstigator()->SetActorLocation(GetActorLocation());
	Destroy();
}


