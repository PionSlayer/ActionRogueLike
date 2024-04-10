// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SBlackHoleProjectile.generated.h"


UCLASS()
class ACTIONROGUELIKE_API ASBlackHoleProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
public:
	ASBlackHoleProjectile();
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;
	UPROPERTY(EditAnywhere)
	float Radius = 1000;
	UPROPERTY(EditAnywhere)
	float Power = 100;
	
	void Tick(float DeltaSeconds) override;
	void OnDissapate() override;
	void OnOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap) override;	
	void BeginPlay() override;
	void Pull();
};
