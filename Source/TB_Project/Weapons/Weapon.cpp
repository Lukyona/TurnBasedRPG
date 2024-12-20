// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"
#include "Global.h"
#include "Components/HealthComponent.h"

AWeapon::AWeapon()
{
	CHelpers::CreateComponent(this, &Root, "Root");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &SkeletalMesh, "SkeletalMesh", Root);
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Capsule, "Capsule", SkeletalMesh);

	Capsule->SetCollisionProfileName("Weapon");
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

ACharacter* AWeapon::GetOwnerCharacter()
{
	return OwnerCharacter? OwnerCharacter : nullptr;
}

void AWeapon::OnCollision()
{
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWeapon::OffCollision()
{
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Hitted.Empty();
}

void AWeapon::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == OwnerCharacter) 
	{
		return;
	}

	UHealthComponent* HealthComp = CHelpers::GetComponent<UHealthComponent>(OtherActor);
	if (HealthComp->IsAlive())
	{
		ApplyDamageToTarget(Cast<ACharacter>(OtherActor));
	}

}
