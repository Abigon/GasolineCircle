// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCPlayerHUDWidget.generated.h"


/*
	����� ��������� ������� ������
	������� �� ����� ������� �������� �����, ���-�� ����� � ���������,
	���-�� �������� � ������ � � ���������.
	� Blueprint ��������� � ������ ������� ���������� � ������, �������� � �������� ������� ��� ������� ����� �����.
	������� ���������� ��������� � �������� ��������. ��� ����������� �������������� ��������� � Blueprint
*/


UCLASS()
class GASOLINECIRCLE_API USGCPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetBulletsInfo() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCoinsAmount() const;

protected:

	virtual void NativeOnInitialized() override;
	
	// ����������� ������ � ���-��� �������� ���, ����� ��� ���� ������ 3 �������
	// ����������� ������� ��������� ������
	FString FormatBullets(int32 BulletsNum) const;

private:
	// ������ �� ASGCMainCharacter, ��� ���������� ���-�� ������
	class ASGCMainCharacter* PlayerPawn = nullptr;
};
