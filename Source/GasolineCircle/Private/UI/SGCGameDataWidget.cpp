// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!


#include "UI/SGCGameDataWidget.h"
#include "Core/SGCGameMode.h"


void USGCGameDataWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// �������������� GameMode
	if (!GetWorld()) return;
	GameMode = Cast<ASGCGameMode>(GetWorld()->GetAuthGameMode());
}

// ���������� ������ � ������� ������ � ����� ���-�� ����
FString USGCGameDataWidget::GetWaveInfo() const
{
	if (!GameMode)	return "0 / 0";
	return FString::Printf(TEXT("Wave %i / %i"), GameMode->GetCurrentWave(), GameMode->GetTotalWaves());
}

// ���������� ������ � ���-��� ���������� ������
FString USGCGameDataWidget::GetWaveLeftEnemies() const
{
	if (!GameMode)	return "Enemies: 0+";
	return FString::Printf(TEXT("Enemies: %i"), GameMode->GetWaveLeftEnemies());
}