// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGCEnemySpawnVolume.generated.h"


/*
	����� ����� ������ �����-������
	����� ���������� ���-�� �����, ������������� � ���������
	��� ������ ���������, ����� �������� ������ �����. �� ����� ����������� ������ �������������� ������� 1 ��������� ������ ��� ������ �����

*/


UCLASS()
class GASOLINECIRCLE_API ASGCEnemySpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGCEnemySpawnVolume();

	// ����� �� ������ �������� ���
	bool IsCanSpawn() const { return SpawningCount > 0; }

	// ����� �� ������ �������� �����
	bool IsCanSpawnBoss() const { return bOnlyBossSpawn; }

	// ������� ��� ������ ����� �������� �����
	int32 GetSpawningCount() const { return SpawningCount; }

	//����� ����
	class ASGCEnemy* SpawnEnemy(TSubclassOf<ASGCEnemy> EnemyClass);

	// ����� ���-�� ������ ����� �� �������� �� ���������
	void Reset() { SpawningCount = DefaultSpawningCount; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UBoxComponent* SpawningBox;

	// ���-�� ��������� ������� ����� �� ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 DefaultSpawningCount = 5;

	// ������� �� ��� ����� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	bool bOnlyBossSpawn = false;

	// ���������� ���-�� ������� �����
	int32 SpawningCount = 0;

	virtual void BeginPlay() override;

	FVector GetSpawnPoint();
};
