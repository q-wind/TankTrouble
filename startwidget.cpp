#include "startwidget.h"
#include "gamemanager.h"
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>


StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
{
    SetUI();
    SetSignalSlot();
}

StartWidget::~StartWidget() {}

void StartWidget::paintEvent(QPaintEvent* event)
{
    // 绘图事件，父类事件处理在前执行默认绘制，随后添加绘制逻辑
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPixmap  img(":/images/fox.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), img);
}

void StartWidget::resizeEvent(QResizeEvent* event)
{
    int newWidth  = event->size().width();
    int newHeight = event->size().height();
    if (static_cast<float>(newWidth) / newHeight > m_aspectRadio) {
        newWidth  = static_cast<int>(newHeight * m_aspectRadio);
    } else {
        newHeight = static_cast<int>(newWidth / m_aspectRadio);
    }
    this->resize(newWidth, newHeight);
    GameManager::GetInstance().m_lastWidth = newWidth;
    GameManager::GetInstance().m_lastHeight = newHeight;
    // 大小调整事件，基类方法可能调整部件大小和位置，先调整窗口再交给父类处理其他位置
    QWidget::resizeEvent(event);
}

void StartWidget::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);
    GameManager::GetInstance().m_lastX = this->x();
    GameManager::GetInstance().m_lastY = this->y();
}

void StartWidget::SetUI()
{
    // widget size
    this->setMinimumSize(600, 450);
    this->setMaximumSize(1000, 750);

    // font
    QFont font;
    font.setFamilies({QString::fromUtf8("Cascadia Code")});
    font.setPointSize(12);
    font.setBold(true);

    // button init setting
    btnStart        = new QPushButton("Start Game");
    btnAIMode       = new QPushButton("1 Player");
    btnLocalMode    = new QPushButton("2 Player");
    btnOnlineMode   = new QPushButton("Online Game");
    btnHelp         = new QPushButton();
    btnStart->setFont(font);
    btnAIMode->setFont(font);
    btnLocalMode->setFont(font);
    btnOnlineMode->setFont(font);
    btnHelp->setIcon(QIcon(":/icons/help.png"));
    btnHelp->setToolTip("Click Fot Help");

    // button size
    const int btnHeight = 60;
    btnStart->setFixedHeight(btnHeight);
    btnStart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnAIMode->setFixedHeight(btnHeight);
    btnAIMode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnLocalMode->setFixedHeight(btnHeight);
    btnLocalMode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnOnlineMode->setFixedHeight(btnHeight);
    btnOnlineMode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnAIMode->setVisible(false);
    btnLocalMode->setVisible(false);
    btnOnlineMode->setVisible(false);
    btnHelp->setFixedSize(40, 40);

    // "start game" button layout
    startLayout = new QHBoxLayout();
    startLayout->addStretch();
    startLayout->addStretch();
    startLayout->addWidget(btnStart);
    startLayout->addStretch();
    startLayout->addStretch();

    // help button layout
    helpLayout = new QHBoxLayout();
    helpLayout->addStretch();
    helpLayout->addWidget(btnHelp);

    // game mode choose button layout
    modeLayout  = new QHBoxLayout();
    modeLayout->addStretch();
    modeLayout->addWidget(btnAIMode);
    modeLayout->addStretch();
    modeLayout->addWidget(btnLocalMode);
    modeLayout->addStretch();
    modeLayout->addWidget(btnOnlineMode);
    modeLayout->addStretch();

    // overall layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(helpLayout);
    mainLayout->addStretch(3);
    mainLayout->addLayout(startLayout);
    mainLayout->addLayout(modeLayout);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void StartWidget::SetSignalSlot()
{
    connect(btnStart, &QPushButton::clicked, this, &StartWidget::ShowGameMode);
    connect(btnHelp, &QPushButton::clicked, this, &StartWidget::ShowHelp);

    connect(btnAIMode, &QPushButton::clicked, this, &StartWidget::SelectAIGame);
    connect(btnLocalMode, &QPushButton::clicked, this, &StartWidget::SelectLocalGame);
    connect(btnOnlineMode, &QPushButton::clicked, this, &StartWidget::SelectOnlineGame);
}

void StartWidget::ShowGameMode()
{
    startLayout->setEnabled(false);
    btnStart->setVisible(false);

    btnAIMode->setVisible(true);
    btnLocalMode->setVisible(true);
    btnOnlineMode->setVisible(true);
}

void StartWidget::ShowHelp()
{
    QMessageBox helpBox;

    helpBox.setWindowIcon(QIcon(":/icons/help.png"));
    helpBox.setWindowTitle("Game Controls");
    helpBox.setIcon(QMessageBox::NoIcon);
    helpBox.setText("Use the following controls:\n\n"
                    "- Player1:\t [WASD] for movement, [SPACE] for shoot\n"
                    "- Player2:\t [ARROW KEY] for movement, [ENTER] for shoot\n"
                    "- ESC:\t\t pause the game\n");
    helpBox.setStandardButtons(QMessageBox::Ok);
    helpBox.setDefaultButton(QMessageBox::Ok);      // 默认选中按钮，回车触发

    helpBox.exec();
}

void StartWidget::SelectAIGame()
{
    emit ModeSelected(Mode::AI);
}

void StartWidget::SelectLocalGame()
{
    emit ModeSelected(Mode::LOCAL);
}

void StartWidget::SelectOnlineGame()
{
    emit ModeSelected(Mode::ONLINE);
}
