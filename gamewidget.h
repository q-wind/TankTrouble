#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "game.h"
#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QKeyEvent>
#include <QCloseEvent>
#include <memory>

class GameWidget: public QWidget
{
    Q_OBJECT

public:
    GameWidget(std::shared_ptr<Game> game, QWidget* parent = nullptr);
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void moveEvent(QMoveEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

signals:
    void ReturnToMenu();

private:
    void SetUI();
    void SetSignalSlot();

    const float m_aspectRadio = 4.0f / 3.0f;
    std::shared_ptr<Game> m_game;
};

#endif // GAMEWIDGET_H
