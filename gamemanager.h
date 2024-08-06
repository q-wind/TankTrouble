#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "startwidget.h"
#include "gamewidget.h"
#include <QObject>
#include <memory>

class StartWidget;
class GameWidget;

class GameManager: public QObject
{
    Q_OBJECT

public:
    static GameManager& GetInstance()
    {
        static GameManager instance;
        return instance;
    }

    void SetStartWidget(StartWidget* widget);
    void SetGameWidget(GameWidget* widget);

    // widget转换时同步大小与位置
    int m_lastWidth;
    int m_lastHeight;
    int m_lastX;
    int m_lastY;

private slots:
    // 监听startWidget的ModeSelected信号，创建currentGame与gameWidget，窗口切换
    void StartGame(Mode mode);
    void Update();
    // 监听gameWidget的ReturnToMenu信号，reset指针，窗口切换
    void EndGame();

private:
    GameManager();
    ~GameManager() = default;
    Q_DISABLE_COPY(GameManager)

    void ShowStartWidget();
    void ShowGameWidget();

    std::unique_ptr<StartWidget> startWidget;
    std::shared_ptr<Game> currentGame;
    std::unique_ptr<GameWidget> gameWidget;
};

#endif // GAMEMANAGER_H
