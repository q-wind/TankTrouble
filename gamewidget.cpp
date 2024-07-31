#include "gamewidget.h"
#include <QPainter>
#include <QPixmap>

GameWidget::GameWidget(GameMode* mode, QWidget* parent):
    QWidget(parent)
{
    SetUI(mode);    // use mode as param ?
    SetSignalSlot();
}

GameWidget::~GameWidget()
{}

void GameWidget::paintEvent(QPaintEvent* event)
{
    // 绘图事件，父类事件处理在前执行默认绘制，随后添加绘制逻辑
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPixmap  img(":/images/fox.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), img);
}

void GameWidget::resizeEvent(QResizeEvent* event)
{
    int newWidth  = event->size().width();
    int newHeight = event->size().height();
    if (static_cast<float>(newWidth) / newHeight > aspectRadio) {
        newWidth  = static_cast<int>(newHeight * aspectRadio);
    } else {
        newHeight = static_cast<int>(newWidth / aspectRadio);
    }
    this->resize(newWidth, newHeight);

    // 大小调整事件，基类方法可能调整部件大小和位置，先调整窗口再交给父类处理其他位置
    QWidget::resizeEvent(event);
}

void GameWidget::SetUI(GameMode* mode)
{

}

void GameWidget::SetSignalSlot()
{

}
