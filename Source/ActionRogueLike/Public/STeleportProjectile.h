// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
	FTimerHandle TeleportDelay;
	bool hit;
	
	void StartTeleportCountDown();
	void Teleport();
public:
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;
	UPROPERTY(EditAnywhere)
	float Delay = 0.05;
	void OnDissapate() override;
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
};
