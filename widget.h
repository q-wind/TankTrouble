#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QResizeEvent>

// Start Widget
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void SetUI();
    void SetSignalSlot();

    const int initWidth   = 800;
    const int initHeight  = 600;
    const float aspectRadio = 4.0f / 3.0f;

    // Qt中自动内存管理，父窗口析构时会负责销毁
    QHBoxLayout* startLayout;
    QPushButton* btnStart;

    QHBoxLayout* modeLayout;
    QPushButton* btnAIMode;
    QPushButton* btnLocalMode;
    QPushButton* btnOnlineMode;

    QVBoxLayout* mainLayout;

private slots:
    void DoShowGameMode();
};
#endif // WIDGET_H
