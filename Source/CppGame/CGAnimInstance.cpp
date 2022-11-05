// Fill out your copyright notice in the Description page of Project Settings.


#include "CGAnimInstance.h"

UCGAnimInstance::UCGAnimInstance() {
	CurrentPawnSpeed = 0.0f;
}

void UCGAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // Access in pawn info
	if (::IsValid(Pawn)) {
		CurrentPawnSpeed = Pawn->GetVelocity().Size(); // get size of velocity vector and update
	}

}

