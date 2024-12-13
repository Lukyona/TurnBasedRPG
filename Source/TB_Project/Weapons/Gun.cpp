// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Gun.h"
#include "Components/CapsuleComponent.h"
#include "Global.h"
#include "Weapons/Bullet.h"

AGun::AGun()
{
    USkeletalMesh* Mesh;
    CHelpers::GetAsset<USkeletalMesh>(&Mesh, "SkeletalMesh'/Game/Weapons/Player/Meshes/Gun/Gun.Gun'");
    SkeletalMesh->SetSkeletalMesh(Mesh);

    MinAttackDistance = 1500.f;

    Capsule->SetRelativeScale3D(FVector::ZeroVector);
    Capsule->SetGenerateOverlapEvents(false);

    CHelpers::GetClass<ABullet>(&BulletClass, "Blueprint'/Game/Weapons/Player/BP_Bullet.BP_Bullet_C'");
}

void AGun::SpawnProjectile()
{
    FTransform BulletTransform = SkeletalMesh->GetSocketTransform("BulletSocket");
    if (BulletClass)
    {
        Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, BulletTransform);
        if (Bullet)
        {
            Bullet->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, "BulletSocket");
        }
    }
}

void AGun::Shoot()
{
    if (!Bullet || !MAINPC)
    {
        return;
    }

    Bullet->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
    FVector Direction = GetOwnerCharacter()->GetCapsuleComponent()->GetForwardVector();
    Bullet->Shoot(Direction);

    --CurBullet;

    MAINPC->UpdateBulletText(CurBullet, MaxBullet);
}

void AGun::Reload()
{
    CurBullet = MaxBullet;
    if(MAINPC)
    {
        MAINPC->UpdateBulletText(CurBullet, MaxBullet);
    }
}
