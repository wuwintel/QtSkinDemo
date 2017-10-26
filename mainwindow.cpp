#include "mainwindow.h"

#include <QApplication>
#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QProgressBar>
#include <QSpinBox>
#include <QSlider>
#include <QScrollBar>

// mainwindow必须要有个centralWidget
MainWindow::MainWindow()
{
    setupUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi()
{
    // ========= 菜单和状态条 =======
    addMenuAndToolBar();

    // ========= 状态条 ============
    addStatusBar();

    // 主操作界面
    QWidget *centerWindow = new QWidget;
    this->setCentralWidget(centerWindow);

    // 设置布局!!!!!
    centerWindow->setLayout(createMainLayout());
}

QLayout* MainWindow::createMainLayout()
{
    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addLayout(groupBoxDemo(), 0, 0);
    mainLayout->addLayout(listViewDemo(), 0, 1);
    mainLayout->addLayout(tableWidgetDemo(), 1, 0);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addLayout(progressBarDemo());
    vbox->addLayout(sliderDemo());
    vbox->addLayout(scrollBarDemo());

    mainLayout->addLayout(vbox,1,1);

    return mainLayout;
}

// 添加菜单和工具条
void MainWindow::addMenuAndToolBar()
{
    QAction *actionOpen = new QAction(tr("&Open"), this);
    actionOpen->setShortcut(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Open a ColorDialog."));
    actionOpen->setIcon(QIcon(":/res/images/fileopen.png"));
    QObject::connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));

    QAction *actionClose = new QAction(tr("E&xit"), this);
    actionClose->setStatusTip(tr("Exit"));
    actionClose->setIcon(QIcon(":/res/images/exit.png"));
    QObject::connect(actionClose, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(actionOpen);
    file->addSeparator();
    file->addAction(actionClose);

    QToolBar *toolbar = addToolBar(tr("&File"));
    toolbar->addAction(actionOpen);
}

void MainWindow::addStatusBar()
{
    QLabel *msgLabel = new QLabel();
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignCenter);

    // 设置边框为0,避免无信息显示的时候有个小竖线
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    statusBar()->addWidget(msgLabel);
}

// ========= 颜色选择 ===========
QLayout *MainWindow::listViewDemo()
{
    QStringListModel *model = new QStringListModel(QColor::colorNames(), this);

    modelProxy = new QSortFilterProxyModel(this);
    modelProxy->setSourceModel(model);
    modelProxy->setFilterKeyColumn(0);

    view = new QListView(this);
    view->setModel(modelProxy);

    QLineEdit *filterInput = new QLineEdit;
    QLabel *filterLabel = new QLabel(tr("Filter"));
    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterInput);

    syntaxBox = new QComboBox;
    syntaxBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    syntaxBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    syntaxBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxBox->addItem(tr("Fixed string"), QRegExp::FixedString);
    QLabel *syntaxLabel = new QLabel(tr("Syntax"));
    QHBoxLayout *syntaxLayout = new QHBoxLayout;
    syntaxLayout->addWidget(syntaxLabel);
    syntaxLayout->addWidget(syntaxBox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(view);
    vbox->addLayout(filterLayout);
    vbox->addLayout(syntaxLayout);

    QObject::connect(filterInput, SIGNAL(textChanged(QString)), this, SLOT(filterChanged(QString)));
    QObject::connect(view, SIGNAL(pressed(QModelIndex)), this, SLOT(viewSelected(QModelIndex)));

    return vbox;
}


void MainWindow::filterChanged(QString text)
{
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(syntaxBox->itemData(syntaxBox->currentIndex()).toInt());
    QRegExp regExp(text, Qt::CaseInsensitive, syntax);
    modelProxy->setFilterRegExp(regExp);
}

void MainWindow::viewSelected(QModelIndex idx)
{
    //view->itemDelegateForRow(idx.row())

    QMessageBox::information(this, "Show Color select", "color is", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

QLayout *MainWindow::tableWidgetDemo()
{
    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setRowCount(5);

    QStringList headers;
    headers << "Line Number" << "ID" << "Name" << "Age" << "Sex";
    table->setHorizontalHeaderLabels(headers);

    table->setItem(0, 0, new QTableWidgetItem(QIcon(":/images/five-pointed-star.png"), QString("1")));
    table->setItem(1, 0, new QTableWidgetItem(QString("2")));
    table->setItem(2, 0, new QTableWidgetItem(QString("3")));
    table->setItem(3, 0, new QTableWidgetItem(QString("4")));
    table->setItem(4, 0, new QTableWidgetItem(QString("5")));
    table->setItem(0, 1, new QTableWidgetItem(tr("20100112")));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(table);

     return vbox;
}

QLayout *MainWindow::groupBoxDemo()
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createFirstExclusiveGroup(),0,0);
    grid->addWidget(createSecondExclusiveGroup(),0,1);
    grid->addWidget(createNonExclusiveGroup(),1,0);
    grid->addWidget(createPushButtonGroup(),1,1);

    return grid;
}

QGroupBox *MainWindow::createFirstExclusiveGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Exclusive Radio Buttons"));
    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
    QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
    QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox *MainWindow::createSecondExclusiveGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("E&xclusive Radio Buttons"));
    groupBox->setCheckable(true);
    groupBox->setChecked(true);

    QRadioButton *radio1 = new QRadioButton(tr("Rad&io button1"));
    QRadioButton *radio2 = new QRadioButton(tr("Radi&o buttoon2"));
    QRadioButton *radio3 = new QRadioButton(tr("Radio &button3"));
    radio1->setChecked(true);
    QCheckBox *checkBox = new QCheckBox(tr("Ind&ependent checkbox"));
    checkBox->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addWidget(checkBox);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox *MainWindow::createNonExclusiveGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("No-Exclusive Checkboxes"));
    groupBox->setFlat(true);

    QCheckBox *checkBox1 = new QCheckBox(tr("&Checkbox 1"));
    QCheckBox *checkBox2 = new QCheckBox(tr("C&heckbox 2"));
    checkBox2->setChecked(true);
    QCheckBox *tristateBox = new QCheckBox(tr("Tri-&state buttton"));

    tristateBox->setTristate(true);//是否启用三种状态切换
    tristateBox->setCheckState(Qt::PartiallyChecked);//介于Qt::Unchecked和Qt::Checked之间

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(checkBox1);
    vbox->addWidget(checkBox2);
    vbox->addWidget(tristateBox);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox *MainWindow::createPushButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("&Push Button"));
    groupBox->setCheckable(true);
    groupBox->setChecked(true);

    QPushButton *pushButton = new QPushButton(tr("&Normal Button"));
    QPushButton *toggleButton = new QPushButton(tr("&Toggle Button"));
    toggleButton->setCheckable(true);
    toggleButton->setChecked(true);

    QPushButton *flatButton = new QPushButton(tr("&Flat Button"));
    flatButton->setFlat(true);

    QPushButton *popupButton = new QPushButton(tr("Pop&up Button"));
    QMenu *menu = new QMenu(this);
    menu->addAction((tr("&First Item")));
    menu->addAction((tr("&Second Item")));
    menu->addAction((tr("Third Item")));
    menu->addAction(tr("F&ourth Item"));
    popupButton->setMenu(menu);

    QAction *newAction = menu->addAction(tr("Submenu"));
    QMenu *subMenu = new QMenu(tr("Popup Submenu"));
    subMenu->addAction(tr("Item 1"));
    subMenu->addAction(tr("Item 2"));
    subMenu->addAction(tr("Item 3"));
    newAction->setMenu(subMenu);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pushButton);
    vbox->addWidget(toggleButton);
    vbox->addWidget(flatButton);
    vbox->addWidget(popupButton);
    groupBox->setLayout(vbox);

    return groupBox;
}

QLayout* MainWindow::progressBarDemo()
{
    QProgressBar *bar1 = new QProgressBar(this);
    bar1->setOrientation(Qt::Horizontal);  // 水平方向
    bar1->setMinimum(0);  // 最小值
    bar1->setMaximum(100);  // 最大值
    bar1->setValue(50);  // 当前进度

    QProgressBar *bar2 = new QProgressBar(this);
    bar2->setOrientation(Qt::Horizontal);  // 水平方向
    bar2->setMinimum(0);  // 最小值
    bar2->setMaximum(100);  // 最大值
    bar2->setValue(50);  // 当前进度
    bar2->setInvertedAppearance(true);  // 反方向

    QProgressBar *bar3 = new QProgressBar(this);
    bar3->setOrientation(Qt::Horizontal);  // 水平方向
    bar3->setMinimum(0);  // 最小值
    bar3->setMaximum(4800);  // 最大值
    bar3->setValue(2000);  // 当前进度
    double dProgress = (bar3->value() - bar3->minimum()) * 100.0 / (bar3->maximum() - bar3->minimum());
    bar3->setFormat(QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(dProgress, 'f', 1)));
    bar3->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  // 对齐方式

    QProgressBar *bar4 = new QProgressBar(this);
    bar4->setOrientation(Qt::Horizontal);  // 水平方向
    bar4->setMinimum(0);  // 最小值
    bar4->setMaximum(0);  // 最大值

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(bar1);
    vbox->addWidget(bar2);
    vbox->addWidget(bar3);
    vbox->addWidget(bar4);

    return vbox;
}

QLayout* MainWindow::sliderDemo()
{
    int nMin = 0;
    int nMax = 200;
    int nSingleStep = 10;

    // 微调框
    QSpinBox *pSpinBox = new QSpinBox(this);
    pSpinBox->setMinimum(nMin);  // 最小值
    pSpinBox->setMaximum(nMax);  // 最大值
    pSpinBox->setSingleStep(nSingleStep);  // 步长

    // 滑动条
    QSlider *pSlider = new QSlider(this);
    pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    pSlider->setMinimum(nMin);  // 最小值
    pSlider->setMaximum(nMax);  // 最大值
    pSlider->setSingleStep(nSingleStep);  // 步长

    // 连接信号槽（相互改变）
    connect(pSpinBox, SIGNAL(valueChanged(int)), pSlider, SLOT(setValue(int)));
    connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));

    pSpinBox->setValue(10);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(pSpinBox);
    hbox->addWidget(pSlider);

    return hbox;
}

QLayout* MainWindow::scrollBarDemo()
{
    int nMin = 0;
    int nMax = 100;
    int nSingleStep = 2;

    // 微调框
    QSpinBox *pSpinBox = new QSpinBox(this);
    pSpinBox->setMinimum(nMin);  // 最小值
    pSpinBox->setMaximum(nMax);  // 最大值
    pSpinBox->setSingleStep(nSingleStep);  // 步长

    // 滑动条
    QScrollBar *pScrollBar = new QScrollBar(Qt::Horizontal, this); // 水平方向
    pScrollBar->setMinimum(nMin);  // 最小值
    pScrollBar->setMaximum(nMax);  // 最大值
    pScrollBar->setSingleStep(nSingleStep);  // 步长

    // 获取大小策略
    QSizePolicy spinSizePolicy = pSpinBox->sizePolicy();
    QSizePolicy scrollbarSizePolicy = pScrollBar->sizePolicy();

    spinSizePolicy.setHorizontalPolicy(QSizePolicy::Maximum);
    pSpinBox->setSizePolicy(spinSizePolicy);
    scrollbarSizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    pScrollBar->setSizePolicy(scrollbarSizePolicy);

    // 连接信号槽（相互改变）
    connect(pSpinBox, SIGNAL(valueChanged(int)), pScrollBar, SLOT(setValue(int)));
    connect(pScrollBar, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));

    pSpinBox->setValue(10);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(pSpinBox);
    hbox->addWidget(pScrollBar);

    return hbox;
}

