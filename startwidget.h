#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include "gamemode.h"
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QResizeEvent>

// Start StartWidget
class StartWidget : public QWidget
{
    Q_OBJECT

public:
    StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void SetUI();
    void SetSignalSlot();

    const float aspectRadio = 4.0f / 3.0f;

    // Qt中自动内存管理，父窗口析构时会负责销毁子部件
    QHBoxLayout* startLayout;
    QPushButton* btnStart;

    QHBoxLayout* helpLayout;
    QPushButton* btnHelp;

    QHBoxLayout* modeLayout;
    QPushButton* btnAIMode;
    QPushButton* btnLocalMode;
    QPushButton* btnOnlineMode;

    QVBoxLayout* mainLayout;

signals:
    void ModeSelected(Mode mode);

private slots:
    void ShowGameMode();
    void ShowHelp();
    void StartAIGame();
    void StartLocalGame();
    void StartOnlineGame();
};
#endif // STARTWIDGET_H
