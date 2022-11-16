// Fill out your copyright notice in the Description page of Project Settings.


#include "CGItemBox.h"
#include "CGWeapon.h"
#include "CGCharacter.h"

// Sets default values
ACGItemBox::ACGItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));


	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f)); // half size of box
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));

	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));

	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false; // we will trigger the particle when a condition satisfied
	}


	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = ACGWeapon::StaticClass();

}

// Called when the game starts or when spawned
void ACGItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACGItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACGItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACGItemBox::OnCharacterBeginOverlap);
}

void ACGItemBox::OnCharacterBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CGLOG_S(Warning);

	auto CGCharacter = Cast<ACGCharacter>(OtherActor);
	CGCHECK(nullptr != CGCharacter);

	if (nullptr != CGCharacter && nullptr != WeaponItemClass)
	{
		if(CGCharacter->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<ACGWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			CGCharacter->SetWeapon(NewWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false); //collision detection off to prevent duplicated particle occurence
			Effect->OnSystemFinished.AddDynamic(this, &ACGItemBox::OnEffectFinished);

		}
		else
		{
			CGLOG(Warning, TEXT("%s can't equip weapon"), *CGCharacter->GetName());
		}
	}
}


void ACGItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}