// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "Items/SGCItem.h"
#include "Weapon/SGCExplosiveDamageType.h"
#include "SGCExplosive.generated.h"


/*
	����� ����.
	���������� �� ���� ����� ������, ��������� � TSet.
	����� �������, ����� ������ �� ���� ������������ ����, ��� ��������� ����, � ������ ����������� � Blueprint
	����� ������ ����������, ��� ���������� ����� ������ ���������� �����, ��� ���������� ����� ��������������.
	���� �� ��������� � �����, � ���������� ����� ����� ����������� �����
*/


UCLASS()
class GASOLINECIRCLE_API ASGCExplosive : public ASGCItem
{
	GENERATED_BODY()

public:
	virtual void OnCollisionVolumeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	// ���� �� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosive")
	float DamageAmount = 3.f;

	// ��� �����. � ������ ���������� ����� ������ ��� ������������ ������ ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosive")
	TSubclassOf<UDamageType> SGCDamageType = USGCExplosiveDamageType::StaticClass();

	// ����� ��������� ���� �� ����� ����� ����� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosive")
	float SecondsToRespawn = 5.f;

	// ����� �������, ������� ����� ���������� �� ����. ������������� � Blueprint. 
	// ��� ������ ����, ��� ����� ������������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosive")
	TSet <TSubclassOf<APawn>> DamagedPawnsClasses;

	virtual void BeginPlay() override;

private:
	// ������ �������������� ����
	FTimerHandle RespawnTimerHandle;

	// ������� �������������� ����
	void Respawn();

};

