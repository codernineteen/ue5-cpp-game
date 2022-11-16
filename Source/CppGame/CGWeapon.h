// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CppGame.h"
#include "GameFramework/Actor.h"
#include "CGWeapon.generated.h"

UCLASS()
class CPPGAME_API ACGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category=Weapon)
		USkeletalMeshComponent* Weapon;

};
