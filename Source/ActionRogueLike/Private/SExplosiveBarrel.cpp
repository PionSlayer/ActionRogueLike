// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh -> SetSimulatePhysics(true);
	Mesh->OnComponentHit.AddDynamic(this,&ASExplosiveBarrel::OnHit);
	RootComponent = Mesh;
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->bIgnoreOwningActor=true;
	RadialForceComponent -> SetupAttachment(Mesh);
	RadialForceComponent -> bImpulseVelChange = true;
	Mesh -> SetCollisionProfileName("PhysicsActor");
	RadialForceComponent ->Radius=2000;

}


// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	

	
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherComp->GetCollisionObjectType() == ECC_GameTraceChannel1)
	{
		Mesh->AddImpulse(OtherActor->GetVelocity()*1000);
		RadialForceComponent->FireImpulse();

		// %s == string
		// %f == float
		
		
		UE_LOG(LogTemp, Warning,TEXT("OtherActor: %s, at game time: %f"),*GetNameSafe(OtherActor),GetWorld()->TimeSeconds);
		UE_LOG(LogTemp, Log,TEXT("OtherActor: %s, at game time: %f"),*GetNameSafe(OtherActor),GetWorld()->TimeSeconds);
		UE_LOG(LogTemp, Error,TEXT("OtherActor: %s, at game time: %f"),*GetNameSafe(OtherActor),GetWorld()->TimeSeconds);


		FString CombineString = FString::Printf(TEXT("BOOM"));
		DrawDebugString(GetWorld(),Hit.ImpactPoint,CombineString,nullptr,FColor::Green,2.0f,true);
	}
}
