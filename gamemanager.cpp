#include "gamemanager.h"
#include "aimode.h"
#include "localmode.h"
#include "onlinemode.h"
#include <QApplication>
#include <QScreen>

GameManager::GameManager()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    m_lastWidth = 800;
    m_lastHeight = 600;
    m_lastX = (screen->geometry().width() - m_lastWidth) / 2;
    m_lastY = (screen->geometry().height() - m_lastHeight) / 2;

}

void GameManager::SetStartWidget(StartWidget* widget)
{
    startWidget.reset(widget);
    connect(startWidget.get(), &StartWidget::ModeSelected, this, &GameManager::StartGame);  // 处理StartWidget的选择游戏模式信号
    ShowStartWidget();
}

void GameManager::SetGameWidget(GameWidget* widget)
{
    gameWidget.reset(widget);
    connect(gameWidget.get(), &GameWidget::ReturnToMenu, this, &GameManager::EndGame);  // 从GameWidget返回主界面信号
    ShowGameWidget();
}

void GameManager::ShowStartWidget()
{
    startWidget->resize(m_lastWidth, m_lastHeight);
    startWidget->move(m_lastX, m_lastY);
    startWidget->show();
    if (gameWidget) {
        gameWidget->hide();
    }
}

void GameManager::ShowGameWidget()
{
    gameWidget->resize(m_lastWidth, m_lastHeight);
    gameWidget->move(m_lastX, m_lastY);
    gameWidget->show();
    if (startWidget) {
        startWidget->hide();
    }
}

// startWidget的ModeSelected信号触发，创建对应游戏模式和窗口
void GameManager::StartGame(Mode mode)
{
    if (currentGame) {
        currentGame->EndGame();
        currentGame.reset();
    }

    switch(mode){
    case Mode::AI:
        currentGame = std::make_shared<AIMode>();
        break;
    case Mode::LOCAL:
        currentGame = std::make_shared<LocalMode>();
        break;
    case Mode::ONLINE:
        currentGame = std::make_shared<OnlineMode>();
        break;
    default:
        break;
    };

    if (currentGame) {
        SetGameWidget(new GameWidget(currentGame));
        ShowGameWidget();
    }
}

void GameManager::Update()
{
    if (currentGame) {
        currentGame->UpdateGame();
    }
}

void GameManager::EndGame()
{

    // return to startwidget
    ShowStartWidget();
}
