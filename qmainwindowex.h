#ifndef QEXMAINWINDOW_H
#define QEXMAINWINDOW_H

#include <QMainWindow>
#include "qtitlebarex.h"

class QMainWindowEx : public QMainWindow
{
    Q_OBJECT
public:
    explicit QMainWindowEx(QMainWindow *parent = nullptr);

public:
    QWidget *centralWindow() const;

signals:

public slots:

private:
    QTitleBarEx *m_titleBar;
    QWidget     *m_centralWidget;
};

#endif // QEXMAINWINDOW_H
