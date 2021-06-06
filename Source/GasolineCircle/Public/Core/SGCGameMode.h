// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGCGameMode.generated.h"


/*
	����� ��������� �������� GameMode.
	������������ ������� ����, �������� ��������� ����, ���������� ����� �����, 
	��������� � ������������ ������� �� ������.

	��������� ����� ����������� ���-�� ����, ���� � ���������� ����� � �����
	����� ������ ����� ������������ ������ �� ��������� �����.
	��������� ����������� ��������� ��� ������ ��������� ������ ����� ����� ������:
	��������������� ��� ��� ��������, ������� � ��������� ��� ��� ������ ����� ����� ������.

	��� ������� ���� ���������� �������� �� ������������ ���-�� ����� � ������ � 
	���-�� ��������� ������� �� ���� ������ ������ ������. ��� �������������� ������ ������
*/


// ������������ ��������� ����
UENUM(Blueprinttype)
enum class ESGCGameState : uint8
{
	EGS_Waiting UMETA(DisplayName = "Game Waiting To Start"),
	EGS_InProgress UMETA(DisplayName = "Game In Progress"),
	EGS_Pause UMETA(DisplayName = "Pause Game"),
	EGS_GameOverWin UMETA(DisplayName = "Win The Game"),
	EGS_GameOverLose UMETA(DisplayName = "Lose The Game "),
	EGS_MAX UMETA(DisplayName = "DefaultMAX")
};

// ��������� ��� ����������� ���� � ���-�� ����� ��� ������ � �����
USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Data")
	TSubclassOf<class ASGCEnemy> EnemyClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Data")
	int32 EnemiesAmount;
};

// ��������� ��� �������� �����. �������� ������ � �����/���-��� �����
// ���-�� �����, ������� ��������� ������������ � ����� ����� �������� �����.
// ���� ���� �� ���� �� ���� ���������� ����� 0, �� ����������� ��� ���� ����� ����� ��� ������
USTRUCT(BlueprintType)
struct FWaveSpawnData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Data")
	TArray<FEnemySpawnData> EnemiesData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Data")
	float SecondsBetweenSpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Data")
	int32 AmountEnemiesSpawnAtOnce;
};

// ������� ������ �������� �� �������
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartBulletsSaleSignature, int32);

// ������� ��������� �������� �� �������
DECLARE_MULTICAST_DELEGATE(FOnFinishBulletsSaleSignature);

// ������� ����� ��������� ����
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, ESGCGameState);

// ������� ������ ������� ����� ������� ����� �����
DECLARE_MULTICAST_DELEGATE(FOnStartWaveTimeCountdownSignature);

// ������� ������ ����� ����� � ��������� �������
DECLARE_MULTICAST_DELEGATE(FOnWaveStartSignature);

UCLASS()
class GASOLINECIRCLE_API ASGCGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	ASGCGameMode();

	FOnStartBulletsSaleSignature OnStartBulletsSale;
	FOnFinishBulletsSaleSignature OnFinishBulletsSale;
	FOnGameStateChangedSignature OnGameStateChanged;
	FOnStartWaveTimeCountdownSignature OnStartWaveTimeCountdown;
	FOnWaveStartSignature OnWaveStart;

	virtual void StartPlay() override;
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

	// ���������� ��������� ��������
	bool IsSale() const { return bIsSale; }

	// ����������� ������� �������� ��� ��������
	int32 GetCurrentPriceOfBullets() const { return CurrentPriceOfBullets; }
	int32 GetBulletsForSale() const { return BulletsForSale; }

	// ��������� ��������
	void EndSale();

	// ����������� ������� ��� �������
	int32 GetCurrentWave() const { return CurrentWave + 1; }
	int32 GetTotalWaves() const { return TotalWaves; }
	int32 GetWaveLeftEnemies() const { return WaveLeftEnemies; }
	float GetWaveStartCountdownTimer() const { return GetWorldTimerManager().GetTimerRemaining(WaveStartCountdownTimerHandle); }

	// ��������� ������ ����� � ������
	void KillEnemy();
	void KillPlayer();


protected:
	// ��������� �������� �� �������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Min value in seconds before the start of a new sale"))
	int32 SecondsToSaleMin = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Max value in seconds before the start of a new sale"))
	int32 SecondsToSaleMax = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Min count of bullets at sale"))
	int32 BulletsForSaleMin = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Max count of bullets at sale"))
	int32 BulletsForSaleMax = 40;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Min price of bullets at sale"))
	int32 PriceOfBulletsMin = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Max price of bullets at sale"))
	int32 PriceOfBulletsMax = 40;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Step in seconds to lower the price at sale"))
	float StepSecondsOfCountdown = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets Sale", meta = (ToolTip = "Price Step to lower the price at sale"))
	int32 StepPriceOfCountdown = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	class USoundCue* SaleStartSound;

	// ��������� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Data", meta = (ToolTip = "Must be at least one wave"))
	TArray<FWaveSpawnData> WaveSpawnData;

	// ����� ��������� ������� ����� ������� ����� �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Data", meta = (ToolTip = "Countdown time before the start of a new wave"))
	float SecondsCountdownToWaveStart = 5.f;

	// ��������� �������������� �������� ����� ����� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "On New Wave", meta = (ToolTip = "Restore the player's bullets to default before the start of a new wave"))
	bool bPlayerBulletsReset = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "On New Wave", meta = (ToolTip = "Restore the player's health to default before the start of a new wave"))
	bool bPlayerHealthRestore = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "On New Wave", meta = (ToolTip = "Reset player's coins before the start of a new wave"))
	bool bPlayerCoinsReset = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "On New Wave", meta = (ToolTip = "Remove coins from map before the start of a new wave"))
	bool bRemoveCoinsFromMap = true;

private:
	// �������
	FTimerHandle NextSaleTimerHandle;
	FTimerHandle SaleCountdownTimerHandle;
	FTimerHandle WaveStartCountdownTimerHandle;
	FTimerHandle WaveSpawnTimerHandle;

	//������� ��������� ��������
	bool bIsSale = false;
	int32 CurrentPriceOfBullets = 0;
	int32 BulletsForSale = 0;

	// ������� ����� �����
	int32 CurrentWave = 0;
	
	// ����� ���-�� ����
	int32 TotalWaves = 0;

	// ���-�� ������ �� ��������� �����
	int32 WaveLeftEnemies = 0;

	// ���������� � ������� �����
	FWaveSpawnData CurrentWaveSpawnData;

	// ������� ���������
	ESGCGameState CurrentGameState = ESGCGameState::EGS_Waiting;

	// ������ ��� ���������� ������
	class ASGCMainCharacter* PlayerCharacter0 = nullptr;
	class ASGCPlayerController* PlayerController0 = nullptr;

	// ��������� ��������
	void StartSale();
	void StopSale();
	void RestartSale();
	void SetCurrentPriceOfBullets();

	// ��������� ��������� �������� �����
	void GameOver(bool bIsWin);
	void WaveOver();
	void StartWave();
	void StopWave(bool IsResetCharacter);
	void PrepareToWave();
	void SpawnWave();
	class ASGCEnemySpawnVolume* GetEnemySpawnVolume();

	// �������� ������ ����� ������� ����
	void CheckLevel();

	// ��������� �������� ��������� ����
	void SetGameState(ESGCGameState State);
};
