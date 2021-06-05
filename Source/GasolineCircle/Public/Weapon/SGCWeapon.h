// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGCWeapon.generated.h"


/*
	����� ������. ����� ������� �������� ��� ������ ����� ������ ��� ����������
	�� ������������ �������������� ����������� ��� ������ ��������. ������ ������.
*/


UCLASS()
class GASOLINECIRCLE_API ASGCWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGCWeapon();

	void StartFire();
	void StopFire();
	void Reload();
	void ResetAmmo();
	void AddBullets(int32 NewBullets);

	bool IsClipEmpty() const { return BulletsInClip == 0; }
	bool IsAmmoEmpty() const { return TotalBullets == 0; }


	// ������� ��� UI
	int32 GetTotalBullets() const { return TotalBullets; }
	int32 GetBulletsInClip() const { return BulletsInClip; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USkeletalMeshComponent* WeaponMesh;

	// ����� ������� 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASGCProjectile>ProjectileClass;

	// ����� ����, ��� ����������� ��������� ����� � ����������� �������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "Muzzle";

	// ����� ����� ���������� ��� ������� ������� ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.5f;

	// ������������ ���-�� �������� � ���������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "Max bullets in inventory"))
	int32 MaxBullets = 90;

	// ������� �������� � ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "Max bullets in one clip"))
	int32 MaxBulletsInClip = 15;

	// ��������� ���-�� �������� � ���������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "Bullets in inventory on game's start"))
	int32 StartBullets = 60;


	// ������ �� �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	class USoundCue* ShotSound;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	class USoundCue* ReloadSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds", meta = (ToolTip = "Sound for shoot when clip is empty"))
	class USoundCue* EmptySound;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void MakeShot();

private:

	// ������ ������������ ��������
	FTimerHandle ShotTimerHandle;

	// ������� ���-�� �������� � ���������
	int32 TotalBullets = 0;

	// ������� ���-�� �������� � ��������
	int32 BulletsInClip = 0;

};
