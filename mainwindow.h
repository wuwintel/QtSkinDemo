#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmainwindowex.h"

#include <QComboBox>
#include <QListView>
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QStringListModel>
#include <QLayout>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    void setupUi();

    void addMenuAndToolBar();
    void addStatusBar();

    QLayout* createMainLayout();

    // ListView demo
    QLayout *listViewDemo();
    QListView *view;
    QSortFilterProxyModel *modelProxy;
    QComboBox *syntaxBox;

    // TableWidget deo,
    QLayout *tableWidgetDemo();

    // GroupBox demo
    QLayout *groupBoxDemo();
    QGroupBox *createFirstExclusiveGroup();
    QGroupBox *createSecondExclusiveGroup();
    QGroupBox *createNonExclusiveGroup();
    QGroupBox *createPushButtonGroup();

    // ProgressBar demo
    QLayout *progressBarDemo();

    // SpinBox Slider demo
    QLayout *sliderDemo();

    // ScrollBar Demo()
    QLayout *scrollBarDemo();

private slots:
    void filterChanged(QString text);
    void viewSelected(QModelIndex idx);
};

#endif // MAINWINDOW_H
