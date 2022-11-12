// Fill out your copyright notice in the Description page of Project Settings.


#include "CGCharacter.h"
#include "CGAnimInstance.h"
#include "DrawDebugHelpers.h"

#define ENABLE_DRAW_DEBUG 1

// Sets default values
ACGCharacter::ACGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));

	if (SKM_CARDBOARD.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SKM_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_WARRIOR(TEXT("/Game/Blueprints/ABP_CGPlayer.ABP_CGPlayer_C"));

	if(ABP_WARRIOR.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(ABP_WARRIOR.Class);
	}

	
	SetControlMode(EControlMode::DIABLO);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f; //Character class has Jump member function already

	IsAttacking = false;

	MaxCombo = 4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CGCharacter"));

	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

// Control mode
void ACGCharacter::SetControlMode(EControlMode ControlMode) {
	CurrentControlMode = ControlMode;

	switch (CurrentControlMode) {
	case EControlMode::GTA:
		ArmLengthTo = 450.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::DIABLO:
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}

// Called when the game starts or when spawned
void ACGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));
		break;
	}


	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}

}

// Called to bind functionality to input
void ACGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("ForwardBackward"), this, &ACGCharacter::ForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("RightLeft"), this, &ACGCharacter::RightLeft);	
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACGCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACGCharacter::LookUp);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACGCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ChangeView"), EInputEvent::IE_Pressed, this, &ACGCharacter::ChangeView);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ACGCharacter::Attack);
}

void ACGCharacter::ForwardBackward(float AxisValue)
{
	
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), AxisValue);
		break;

	case EControlMode::DIABLO:
		DirectionToMove.X = AxisValue;
		break;
	}
}

void ACGCharacter::RightLeft(float AxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), AxisValue);
		break;

	case EControlMode::DIABLO:
		DirectionToMove.Y = AxisValue;
		break;
	}
}
// Y-axis control rotation
void ACGCharacter::Turn(float AxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(AxisValue);
		break;
	}
}

void ACGCharacter::LookUp(float AxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(AxisValue);
		break;
	}
}


void ACGCharacter::ChangeView() 
{
	if (CurrentControlMode == EControlMode::GTA)
	{
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
	}
	else
	{
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);
	}
}

void ACGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CGAnim = Cast<UCGAnimInstance>(GetMesh()->GetAnimInstance());
	CGCHECK(nullptr != CGAnim);

	CGAnim->OnMontageEnded.AddDynamic(this, &ACGCharacter::OnAttackMontageEnded);

	CGAnim->OnNextAttackCheck.AddLambda([this]() {
		CGLOG_S(Warning);
		CanNextCombo = false;

		if (IsComboInputOn)
		{
			AttackStartComboState();
			CGAnim->JumpToAttackMontageSection(CurrentCombo);
		}
		}
	);

	CGAnim->OnAttackHitCheck.AddUObject(this, &ACGCharacter::AttackCheck);
}

void ACGCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CGCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ACGCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void ACGCharacter::Attack() {
	if (IsAttacking) {
		CGCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		CGCHECK(CurrentCombo == 0);
		AttackStartComboState();
		CGAnim->PlayAttackMontage();
		CGAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void ACGCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	//collision detection - sweep single by channel
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(), 
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,//identity quaternion
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params
	);
	//Debug drawing code
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifetime = 5.0f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifetime
	);
#endif

	if (bResult)
	{
		//there is no IsValid in ue5 c++
		if (HitResult.GetActor()->IsValidLowLevel())
		{
			CGLOG(Warning, TEXT("Hit Actor Name: %s"), *HitResult.GetActor()->GetName());

			//Damage transmission
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}

void ACGCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInteruppted)
{
	CGCHECK(IsAttacking);
	CGCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

float ACGCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CGLOG(Warning, TEXT("Actor: %s took damage(%f)"), *GetName(), FinalDamage);

	if (FinalDamage > 0.0f)
	{
		CGAnim->SetDeadAnim();
		SetActorEnableCollision(false); // if dead, no collision
	}

	return FinalDamage;
}