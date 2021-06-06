// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGCMainCharacter.generated.h"


/*
	����� ������.
	�������� � ���������.
	���������� ���������� ������/����� � ������ ������/�����.
	������� �������������� �����. ����� ����� �� �����.
	������������ ���������� �������, ������� ���������� ��������, ���� �����
	���-�� ����� ������ ��������������� � HealthComponent.
	�������� ��������� ��������������� � CharacterMovementComponent.
	������ ���������� � WeaponComponent.
*/

UCLASS()
class GASOLINECIRCLE_API ASGCMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// ������ ��� �������
	int32 GetCoinAmount() const { return CoinAmount; }

	// ���������� ����� ��� ����
	void AddCoins(int32 Coins);

	// ������������� ��������� ���������� ��������� ����� ������� ����� �����
	void ResetPlayer(bool bIsRestoreHealth, bool bIsResetAmmo, bool bIsResetCoins);

	ASGCMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class USGCWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
	FORCEINLINE class USGCHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USGCWeaponComponent* WeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USGCHealthComponent* HealthComponent;

	// �������� �������� ���������. ������������ � ����������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rotate")
	float BaseTurnRate = 45.f;

	// ��������� ��� ���� ������. � ������� �� �����������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	float CameraZoomMax = 3000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	float CameraZoomMin = 600.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	float CameraZoomSpeed = 200.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	float CameraZoomDefault = 1600.f;

	// ����� ��� �������� � ��������� ������� �� ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	class USoundCue* SaleSuccessSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	class USoundCue* SaleErrorSound;

	// ����������� ��������� ���-�� ����� � ���������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Coin", meta = (ToolTip = "If equal to 0 then unlimited"))
	int32 MaxCoinAmount = 0.f;

	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void CameraZoomIn();
	void CameraZoomOut();
	void RotateToCursor();

	void OnDeath();

private:
	// ������� ���-�� ����� 
	int32 CoinAmount = 0;

	class APlayerController* CharacterConstroller = nullptr;

	// ������� ��� ������ � ���������
	bool BuyBullets(int32 Coins, int32 Bullets);
	void TryBuyBullets();

	// �������� ����������� ��������� �������� ��-�� �����
	bool CanPay(int32 Price) const { return CoinAmount >= Price; }
};
