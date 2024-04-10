#include "SBaseProjectile.h"
#include "Particles/ParticleSystemComponent.h"

ASBaseProjectile::ASBaseProjectile()
{
	//SPHERE COMPONENT
	PrimaryActorTick.bCanEverTick= true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp-> OnComponentHit.AddDynamic(this,&ASBaseProjectile::OnHit);
	SphereComp-> OnComponentBeginOverlap.AddDynamic(this,&ASBaseProjectile::OnOverlap);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	SphereComp->SetSimulatePhysics(false);
	

	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle -> SetupAttachment(SphereComp);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	ProjectileMovement -> ProjectileGravityScale = 0.0f;
	ProjectileMovement -> InitialSpeed = Speed;
	ProjectileMovement -> bRotationFollowsVelocity = true;
	ProjectileMovement -> bInitialVelocityInLocalSpace = true;

}



void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	SpawnLocation = SphereComp->GetComponentLocation();
}

void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(UseRange)
	{
		float distance = FVector::Distance(GetActorLocation(),SpawnLocation);
		if(distance >= Range){OnDissapate();}
	}
	
}

void ASBaseProjectile::OnDissapate()
{
	
}

void ASBaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
}

void ASBaseProjectile::OnOverlap(UPrimitiveComponent* HitComponent,AActor* OtherActor, UPrimitiveComponent* OtherComponent,int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap)
{
}
