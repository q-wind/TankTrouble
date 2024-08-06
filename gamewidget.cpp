#include "gamewidget.h"
#include "gamemanager.h"
#include <QPainter>
#include <QPixmap>

GameWidget::GameWidget(std::shared_ptr<Game> game, QWidget* parent):
    QWidget(parent), m_game(std::move(game))
{
    // std::cout << m_game.use_count() << std::endl;    // 2
    SetUI();
    SetSignalSlot();
}

GameWidget::~GameWidget()
{}

void GameWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPixmap  img(":/images/fox.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), img);
}

void GameWidget::resizeEvent(QResizeEvent* event)
{
    int newWidth  = event->size().width();
    int newHeight = event->size().height();
    // 仍有待修改，横拉或竖拉 大小没变化
    if (static_cast<float>(newWidth) / newHeight > m_aspectRadio) {
        newWidth  = static_cast<int>(newHeight * m_aspectRadio);
    } else {
        newHeight = static_cast<int>(newWidth / m_aspectRadio);
    }
    this->resize(newWidth, newHeight);
    GameManager::GetInstance().m_lastWidth = newWidth;
    GameManager::GetInstance().m_lastHeight = newHeight;

    QWidget::resizeEvent(event);
}

void GameWidget::moveEvent(QMoveEvent *event)
{
    QWidget::moveEvent(event);
    // event->pos().x() 和 y() 有些许不妥 偏移
    GameManager::GetInstance().m_lastX = this->x();
    GameManager::GetInstance().m_lastY = this->y();
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{

}

void GameWidget::closeEvent(QCloseEvent* event)
{
    // pause game?
    // 暂停后询问确认后退出，处理游戏内资源释放？ gameManager只负责置空该gamewidget指针

    emit ReturnToMenu();
}

void GameWidget::SetUI()
{
    // widget size
    this->setMinimumSize(600, 450);
    this->setMaximumSize(1000, 750);


}

void GameWidget::SetSignalSlot()
{

}
