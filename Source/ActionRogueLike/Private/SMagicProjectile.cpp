#include "SMagicProjectile.h"
#include "Particles/ParticleSystemComponent.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	//SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp -> SetCollisionObjectType(ECC_WorldStatic);
	//SphereComp -> SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp -> SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//SphereComp -> SetCollisionProfileName("Projectile");
	//RootComponent = SphereComp;
	
	//Particle = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	//Particle -> SetupAttachment(SphereComp);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	ProjectileMovement -> InitialSpeed = 1000.0f;
	ProjectileMovement -> bRotationFollowsVelocity = true;
	ProjectileMovement -> bInitialVelocityInLocalSpace = true;
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

