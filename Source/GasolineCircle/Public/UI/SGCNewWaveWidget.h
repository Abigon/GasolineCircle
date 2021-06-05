// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCNewWaveWidget.generated.h"


/*
	����� ������� ��� ����������� ��������� ������� ����� ������� ����� ����� �����,
	�������� ������ ������� ��������� HUD ������
	������� ���������� ��������� ��������. ��� ����������� �������������� ��������� � Blueprint
*/


UCLASS()
class GASOLINECIRCLE_API USGCNewWaveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetLeftSeconds() const;

protected:

	virtual void NativeOnInitialized() override;

	void OnStartCountdown();
	void OnFinishCountdown();

private:
	// ������ �� GameMode, ��� ���������� ���-�� ������
	class ASGCGameMode* GameMode = nullptr;
};
