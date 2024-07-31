#include "gamemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameManager& manager = GameManager::GetInstance();
    manager.SetStartWidget(new StartWidget());
    manager.ShowStartWidget();
    return app.exec();
}
