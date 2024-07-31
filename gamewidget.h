#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "gamemode.h"
#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>

class GameWidget: public QWidget
{
    Q_OBJECT

public:
    GameWidget(GameMode* mode, QWidget* parent = nullptr);
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void SetUI(GameMode* mode);
    void SetSignalSlot();

    const float aspectRadio = 4.0f / 3.0f;
};

#endif // GAMEWIDGET_H
