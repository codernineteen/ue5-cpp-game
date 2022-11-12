// Fill out your copyright notice in the Description page of Project Settings.


#include "CGAnimInstance.h"

UCGAnimInstance::UCGAnimInstance() {
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Animations/Sk_Warrior_Montage.Sk_Warrior_Montage"));

	if (ATTACK_MONTAGE.Succeeded()) {
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UCGAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // Access in pawn info
	if (!::IsValid(Pawn)) return;
	
	if(!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size(); // get size of velocity vector and update

		auto Character = Cast<ACharacter>(Pawn); // Pawn -> Cast
		if (Character) 
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}

}

void UCGAnimInstance::PlayAttackMontage() 
{
	CGCHECK(!IsDead);
	Montage_Play(AttackMontage, 1.0f);
}


void UCGAnimInstance::JumpToAttackMontageSection(int32 NewSection) {
	CGCHECK(!IsDead);
	CGCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UCGAnimInstance::AnimNotify_AttackHitCheck() {
	CGLOG_S(Warning);
	OnAttackHitCheck.Broadcast();
}

void UCGAnimInstance::AnimNotify_NextAttackCheck() {
	CGLOG_S(Warning);
	OnNextAttackCheck.Broadcast();
}

FName UCGAnimInstance::GetAttackMontageSectionName(int32 Section) {
	CGCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
