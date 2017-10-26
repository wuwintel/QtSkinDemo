#include "qtitlebarex.h"
#include <QStyle>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

// Qt窗口的标题栏自绘,  http://www.cnblogs.com/findumars/p/5624822.html
// Qt之自定义界面（添加自定义标题栏） http://blog.csdn.net/liang19890820/article/details/50555298
// Qt 扁平化MainWindow以及自定义标题栏

QTitleBarEx::QTitleBarEx(QWidget *parent) : QWidget(parent)
{
    // Don't let this widget inherit the parent's backround color
    setAutoFillBackground(true);

    // Use a brush with a Highlight color role to render the background
    setBackgroundRole(QPalette::Highlight);

    minimize = new QToolButton(this);
    maximize = new QToolButton(this);
    close= new QToolButton(this);

    // Use the style to set the button pixmaps
    QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    close->setIcon(pix);

    maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    maximize->setIcon(maxPix);

    pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    minimize->setIcon(pix);

    restorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

    minimize->setMinimumHeight(20);
    close->setMinimumHeight(20);
    maximize->setMinimumHeight(20);

    // 这段代码需要调整
    QLabel *label = new QLabel(this);
    label->setText("Window Title");
    parent->setWindowTitle("Window Title");

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addWidget(label);
    hbox->addWidget(minimize);
    hbox->addWidget(maximize);
    hbox->addWidget(close);

    hbox->insertStretch(1, 500);
    hbox->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    maxNormal = false;

    connect(close, SIGNAL( clicked() ), parent, SLOT(close() ) );
    connect(minimize, SIGNAL( clicked() ), this, SLOT(showSmall() ) );
    connect(maximize, SIGNAL( clicked() ), this, SLOT(showMaxRestore() ) );
}

void QTitleBarEx::showSmall()
{
    parentWidget()->showMinimized();
}

void QTitleBarEx::showMaxRestore()
{
    if (maxNormal)
    {
        parentWidget()->showNormal();
        maxNormal = !maxNormal;
        maximize->setIcon(maxPix);
    }
    else
    {
        parentWidget()->showMaximized();
        maxNormal = !maxNormal;
        maximize->setIcon(restorePix);
    }
}

void QTitleBarEx::mousePressEvent(QMouseEvent *me)
{
    startPos = me->globalPos();
    clickPos = mapToParent(me->pos());
}

void QTitleBarEx::mouseMoveEvent(QMouseEvent *me)
{
    if (maxNormal)
    {
        return;
    }

    parentWidget()->move(me->globalPos() - clickPos);
}


