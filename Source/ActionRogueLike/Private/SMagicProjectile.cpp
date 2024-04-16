#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
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
	ParticleSystem= CreateDefaultSubobject<UParticleSystem>("ParticleSystem");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	ProjectileMovement -> InitialSpeed = 1000.0f;
	ProjectileMovement -> bRotationFollowsVelocity = true;
	ProjectileMovement -> bInitialVelocityInLocalSpace = true;


}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	UseOnOverlap();
	SphereComp -> SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	SphereComp -> SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
}
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ASMagicProjectile::OnOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap)
{
	if(OtherActor){
		if(OtherActor!=GetInstigator()){
			USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
			if(AttributeComp){
				AttributeComp->ApplyHeathChange(-20.0f);
			}
			if(ParticleSystem){
				UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				ParticleSystem,
				SphereComp->GetComponentLocation(),
				FRotator::ZeroRotator,
				true);}
				
			Destroy();
		}
		return;
	}
	if(ParticleSystem){
		UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ParticleSystem,
		SphereComp->GetComponentLocation(),
		FRotator::ZeroRotator,
		true);}
				
	Destroy();
}

