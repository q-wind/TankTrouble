#include "gamemanager.h"
#include "aimode.h"
#include "localmode.h"
#include "onlinemode.h"

void GameManager::SetStartWidget(StartWidget* widget)
{
    startWidget.reset(widget);
    connect(startWidget.get(), &StartWidget::ModeSelected, this, &GameManager::StartGame);
}

void GameManager::SetGameWidget(GameWidget* widget)
{
    gameWidget.reset(widget);
}

void GameManager::ShowStartWidget()
{
    if (gameWidget) {
        gameWidget->hide();
    }
    startWidget->show();
}

void GameManager::ShowGameWidget()
{
    gameWidget->show();
    if (startWidget) {
        startWidget->hide();
    }
}

// startWidget的ModeSelected信号触发，创建对应游戏模式和窗口
void GameManager::StartGame(Mode mode)
{
    if (currentMode) {
        currentMode->EndGame();
    }

    switch(mode){
    case Mode::AI:
        currentMode = std::make_unique<AIMode>();
        break;
    case Mode::LOCAL:
        currentMode = std::make_unique<LocalMode>();
        break;
    case Mode::ONLINE:
        currentMode = std::make_unique<OnlineMode>();
        break;
    };

    if (currentMode) {
        SetGameWidget(new GameWidget(currentMode.get()));
        ShowGameWidget();
    }
}

void GameManager::Update()
{
    if (currentMode) {
        currentMode->UpdateGame();
    }
}
