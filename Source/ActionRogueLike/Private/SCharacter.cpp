// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"


ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	AttackAnim = CreateDefaultSubobject<UAnimMontage>("AttackAnim");
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}





void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &ASCharacter::MoveSideways);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &ACharacter::Jump);
	
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract",IE_Pressed,this, &ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(),Value);
}
void ASCharacter::MoveSideways(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,Value);
}


void ASCharacter::PrimaryAttack()
{
	if(ensure(ProjectileClass))
	{
		PlayAnimMontage(AttackAnim);
		GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this,&ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	}
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{

	FVector start = CameraComp->GetComponentLocation();
	FRotator direction = GetControlRotation();
	FVector end = start + (direction.Vector()*1000);

	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_WorldDynamic);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit,start,end,params);

	FVector hitLocation;
	AActor* HitActor = Hit.GetActor();
	if(HitActor)
	{
		hitLocation=Hit.ImpactPoint;
	}
	else
	{
		hitLocation = end;
	}

	DrawDebugSphere(GetWorld(),hitLocation,5,32,FColor::Red,false,2,0,2);
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	
	
	
	
	FTransform SpawnTM = FTransform(UKismetMathLibrary::FindLookAtRotation(HandLocation,hitLocation), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	if(InteractionComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Called:3"));
		InteractionComp->PrimaryInteract();
	}
}
