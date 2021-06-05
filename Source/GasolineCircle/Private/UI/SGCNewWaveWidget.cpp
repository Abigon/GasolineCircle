// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!


#include "UI/SGCNewWaveWidget.h"
#include "Core/SGCGameMode.h"



void USGCNewWaveWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	// �������������� GameMode
	if (!GetWorld()) return;
	GameMode = Cast<ASGCGameMode>(GetWorld()->GetAuthGameMode());

	// ������������� �� ������� ������ ��������� ������ � ��� ���������
	if (GameMode)
	{
		GameMode->OnStartWaveTimeCountdown.AddUObject(this, &USGCNewWaveWidget::OnStartCountdown);
		GameMode->OnWaveStart.AddUObject(this, &USGCNewWaveWidget::OnFinishCountdown);
	}
}

// ���������� ������ ��� ������ �������
void USGCNewWaveWidget::OnStartCountdown()
{
	SetVisibility(ESlateVisibility::Visible);
}

// ������ ������ ��� ��������� �������
void USGCNewWaveWidget::OnFinishCountdown()
{
	SetVisibility(ESlateVisibility::Hidden);
}


// ���������� ����� ��������� ������� ��� Go!
FString USGCNewWaveWidget::GetLeftSeconds() const
{
	if (!IsVisible()) return "";

	int32 TimeToWave = GameMode ? GameMode->GetWaveStartCountdownTimer() : 0;
	if (TimeToWave < 1) return "Go!";
	return FString::FromInt(TimeToWave);
}

