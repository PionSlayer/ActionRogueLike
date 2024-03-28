// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere);
	UProjectileMovementComponent* MovementComp;
	
	UPROPERTY(VisibleAnywhere);
	UParticleSystemComponent* EffectComp;

	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
