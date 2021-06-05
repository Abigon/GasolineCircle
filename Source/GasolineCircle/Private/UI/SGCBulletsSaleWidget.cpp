// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!


#include "UI/SGCBulletsSaleWidget.h"
#include "Core/SGCGameMode.h"

void USGCBulletsSaleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	// �������������� GameMode
	if (!GetWorld()) return;
	GameMode = Cast<ASGCGameMode>(GetWorld()->GetAuthGameMode());

	// ������������� �� ������� ������ � ��������� �������� � GameMode 
	if (GameMode)
	{
		GameMode->OnStartBulletsSale.AddUObject(this, &USGCBulletsSaleWidget::OnStartSale);
		GameMode->OnFinishBulletsSale.AddUObject(this, &USGCBulletsSaleWidget::OnFinishSale);
	}
}


// ������ ��������. �������������� ���-�� �������� � ����������� � ���������� ������ � HUD
void USGCBulletsSaleWidget::OnStartSale(int32 Bullets)
{
	BulletsAmount = Bullets;
	SetVisibility(ESlateVisibility::Visible);
}

// �������� ������ ��� ��������� ��������
void USGCBulletsSaleWidget::OnFinishSale()
{
	SetVisibility(ESlateVisibility::Hidden);
}


// ���������� ������� ���� �����������
int32 USGCBulletsSaleWidget::GetPriceOfBullets() const
{
	// ���� ������ �����, ������ �� ������������
	if (!IsVisible()) return 0;

	return GameMode ? GameMode->GetCurrentPriceOfBullets() : 0;
}

