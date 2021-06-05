// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGCItem.generated.h"


/*
	������� ����� ��� ��������� ������.
	������������ �������� �����, �������������� �� �����, 
	�������� ����������� ������� ��� ���������� �����
	���������� ���� � ������ ������ ��� ���������� �����. ���� ������� ��� ������������, �� � ������ ������ �� ����������, ������ � �����������.
*/


UCLASS()
class GASOLINECIRCLE_API ASGCItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGCItem();
	virtual void Tick(float DeltaTime) override;


	// ����������� �������, ���������� ��� ���������� CollisionVolume
	UFUNCTION()
	virtual void OnCollisionVolumeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class USphereComponent* CollisionVolume;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UStaticMeshComponent* Mesh;

	// ���� � ������ ����������, ���������� � Blueprint. ��� ������ �� �������������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Effects")
	class USoundCue* PickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effects")
	class UParticleSystem* PickupParticles;

	// ��������� ��� �������� �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Rotation")
	bool bRotate = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Rotation", meta = (EditCondition = "bRotate"), meta = (ToolTip = "Rotation Speed"))
	float RotationRate = 90.f;

	virtual void BeginPlay() override;

	// ����������� ���� � ������ ���������� �������
	// ����� ������� � �����������. � ������� ������ �� ����������
	void PlayEffects();
};
