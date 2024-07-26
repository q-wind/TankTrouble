#include "widget.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    SetUI();
    SetSignalSlot();
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent* event)
{
    // 绘图事件，父类事件处理在前执行默认绘制，随后添加绘制逻辑
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPixmap  img(":/images/fox.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), img);
}

void Widget::resizeEvent(QResizeEvent* event)
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

void Widget::SetUI()
{
    this->resize(initWidth, initHeight);

    btnStart        = new QPushButton("开始游戏", this);
    btnAIMode       = new QPushButton("人机对战");
    btnLocalMode    = new QPushButton("多人对战");
    btnOnlineMode   = new QPushButton("联机对战");

    // button size
    btnStart->setFixedHeight(60);
    btnStart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnAIMode->setFixedHeight(60);
    btnAIMode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnAIMode->setVisible(false);
    btnLocalMode->setFixedHeight(60);
    btnLocalMode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnLocalMode->setVisible(false);
    btnOnlineMode->setFixedHeight(60);
    btnOnlineMode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnOnlineMode->setVisible(false);

    // layout
    startLayout = new QHBoxLayout();
    startLayout->addStretch();
    startLayout->addWidget(btnStart);
    startLayout->addStretch();

    modeLayout  = new QHBoxLayout();
    modeLayout->addStretch();
    modeLayout->addWidget(btnAIMode);
    modeLayout->addWidget(btnLocalMode);
    modeLayout->addWidget(btnOnlineMode);
    modeLayout->addStretch();

    mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(2);
    mainLayout->addLayout(startLayout);
    mainLayout->addLayout(modeLayout);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void Widget::SetSignalSlot()
{
    connect(btnStart, &QPushButton::clicked, this, &Widget::DoShowGameMode);
}

void Widget::DoShowGameMode()
{
    startLayout->setEnabled(false);
    btnStart->setVisible(false);

    btnAIMode->setVisible(true);
    btnLocalMode->setVisible(true);
    btnOnlineMode->setVisible(true);
}
