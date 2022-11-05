// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPawn.h"

// Sets default values
ACGPawn::ACGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	//Adjust capsule size to fit it into our pawn
	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0, 0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	
	if (SK_CARDBOARD.Succeeded()) {
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}
	

	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ABP(TEXT("/Game/Blueprints/ABP_CGPlayer.ABP_CGPlayer_C"));

	if (WARRIOR_ABP.Succeeded()) {
		Mesh->SetAnimInstanceClass(WARRIOR_ABP.Class);
	}

}

// Called when the game starts or when spawned
void ACGPawn::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void ACGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("ForwardBackward"), this, &ACGPawn::ForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("RightLeft"), this, &ACGPawn::RightLeft);

}

void ACGPawn::ForwardBackward(float AxisValue) {
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ACGPawn::RightLeft(float AxisValue) {
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ACGPawn::PostInitializeComponents() {
	Super::PostInitializeComponents();
	CGLOG_S(Warning);
}

