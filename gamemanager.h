#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "startwidget.h"
#include "gamemode.h"
#include "gamewidget.h"
#include <QObject>
#include <memory>

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
    void ShowStartWidget();
    void ShowGameWidget();

private slots:
    void StartGame(Mode mode);
    void Update();
private:
    GameManager() = default;
    ~GameManager() = default;
    Q_DISABLE_COPY(GameManager)

    std::unique_ptr<StartWidget> startWidget;
    std::unique_ptr<GameMode> currentMode;
    std::unique_ptr<GameWidget> gameWidget;
};

#endif // GAMEMANAGER_H
