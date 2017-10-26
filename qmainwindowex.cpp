#include "qmainwindowex.h"

#include <QVBoxLayout>

QMainWindowEx::QMainWindowEx(QMainWindow *parent) : QMainWindow(parent)
{
    // Make this a borderless window which can't
    // be resized or moved via the window system

    // 设置成无系统框模式
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    m_titleBar = new QTitleBarEx(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(m_titleBar);
    vbox->setMargin(0);
    vbox->setSpacing(0);

    installEventFilter(vbox);

     //m_centralWidget = new QWidget(this);
     //m_centralWidget->setLayout(vbox);

     //this->setCentralWidget(m_centralWidget);
}

QWidget *QMainWindowEx::centralWindow() const
{
    return this->m_centralWidget;
}
