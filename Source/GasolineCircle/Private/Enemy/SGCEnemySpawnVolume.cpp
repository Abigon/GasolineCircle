// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!


#include "Enemy/SGCEnemySpawnVolume.h"
#include "Enemy/SGCEnemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"


ASGCEnemySpawnVolume::ASGCEnemySpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetBoxExtent(FVector(32, 32, 200));
}

void ASGCEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	Reset();
}

// ����� ���� ��������� ������
ASGCEnemy* ASGCEnemySpawnVolume::SpawnEnemy(TSubclassOf<ASGCEnemy> EnemyClass)
{
	if (!IsCanSpawn() || !GetWorld()) return nullptr;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* Actor = GetWorld()->SpawnActor<AActor>(EnemyClass, GetSpawnPoint(), GetActorRotation(), SpawnParams);
	if (Actor) SpawningCount--;
	return Cast<ASGCEnemy>(Actor);
}


// ���������� ����� ������ ���� � �������� SpawningBox
// ���� ������� ����� � ����� �����, �� ��� ������������ ������ � ����� ����� 
//��-�� �������� ��� ����� ��������� ���� � �����
FVector ASGCEnemySpawnVolume::GetSpawnPoint()
{
	FVector Extent = SpawningBox->GetScaledBoxExtent();
	FVector Origin = SpawningBox->GetComponentLocation();

	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

	return FVector(Point.X, Point.Y, Extent.Z);
}
