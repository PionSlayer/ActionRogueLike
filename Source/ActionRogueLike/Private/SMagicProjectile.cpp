#include "SMagicProjectile.h"
#include "Particles/ParticleSystemComponent.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp -> SetCollisionObjectType(ECC_WorldStatic);
	//SphereComp -> SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp -> SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp -> SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp -> SetupAttachment(SphereComp);
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp -> InitialSpeed = 1000.0f;
	MovementComp -> bRotationFollowsVelocity = true;
	MovementComp -> bInitialVelocityInLocalSpace = true;
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

