// Gasoline Circle. Skillbox's Gamebox test, All Right Reserved!!


#include "MainMenu/SGCMainMenuWidget.h"
#include "Core/SGCGameInstance.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


void USGCMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USGCMainMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USGCMainMenuWidget::OnQuitGame);
    }
}


// ���������� ��� ������� �� ������ ������� ����
// �������� �������� ���������� ������ �� GameInstance
// ��� ��� ���������� ������� � ��� ��������� � ������ �� ��������
void  USGCMainMenuWidget::OnStartGame()
{
    if (!GetWorld()) return;
    const auto SGCGameInstance = GetWorld()->GetGameInstance<USGCGameInstance>();
    if (!SGCGameInstance) return;

    if (SGCGameInstance->GetStartLevelName().IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("Start level name is NONE"));
        return;
    }
    UGameplayStatics::OpenLevel(this, SGCGameInstance->GetStartLevelName());
}

// ������� �� ���� ��� ������� ��������������� ������
void  USGCMainMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
