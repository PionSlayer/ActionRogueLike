// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SBaseProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBaseProjectile();

protected:
	UPROPERTY(EditAnywhere)
	bool UseRange = false;
	UPROPERTY(EditAnywhere)
	float Range = 1000;
	FVector SpawnLocation;
    
	UPROPERTY(EditAnywhere)
	float Speed = 1000;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComp;
                           	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
                           	
	UPROPERTY(VisibleAnywhere);
	UParticleSystemComponent* Particle;


	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual	void OnDissapate();
	UFUNCTION()
	virtual	void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual	void OnOverlap(UPrimitiveComponent* HitComponent,AActor* OtherActor, UPrimitiveComponent* OtherComponent,int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap);
    	

};
