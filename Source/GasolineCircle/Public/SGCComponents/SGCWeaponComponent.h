// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGCWeaponComponent.generated.h"


/*
	����� ���������� ������ ��� �����.
	����� ��������� ��� ������������� ���������� ����� ������ (������� ������ � ������� � ������� ������� �� ����� ������.
	�������� ���������� ����� ���������� � ���������� �������.
	� ���������� ����� �� ������ ���� ����� �������� ��� ����� ������ � ��������� ���� ���������� � Character

*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASOLINECIRCLE_API USGCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGCWeaponComponent();

	virtual void StartFire();
	void StopFire();
	void Reload();
	void ResetDefaultAmmo();
	void AddCurrentBullets(int32 Bullets);


	// ������� ��� ��������
	int32 GetCurrentTotalBullets() const;
	int32 GetCurrentBulletsInClip() const;

protected:
	// ����� ������ ��� ������ ��� ������ ����. ���������� � Blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASGCWeapon> WeaponClass;

	// �������� ������ �� ������� ��������� ��� ������ ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponSocketName = "WeaponSocket";

	// �������� ��������� ������
	UPROPERTY()
	ASGCWeapon* CurrentWeapon = nullptr;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SpawnWeapon();		
};
