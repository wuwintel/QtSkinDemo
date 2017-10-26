#ifndef QTITLEBAREX_H
#define QTITLEBAREX_H

#include <QToolButton>
#include <QWidget>

// 为窗口定制标题栏，替代系统本身自带的标题栏, 美化界面
class QTitleBarEx : public QWidget
{
    Q_OBJECT

public:
    explicit QTitleBarEx(QWidget *parent);

signals:

public slots:
    void showSmall();
    void showMaxRestore();

protected:

    // 双击标题栏进行界面的最大化/还原事件处理
    //virtual void mouseDoubleClickEvent(QMouseEvent *event);

    // 鼠标移动
    void mousePressEvent(QMouseEvent *event);

    // 鼠标按下
    void mouseMoveEvent(QMouseEvent *event);

private:
    QToolButton *minimize;      // 最小化按钮
    QToolButton *maximize;      // 最大化按钮
    QToolButton *close;         // 关闭按钮

    QPixmap restorePix, maxPix;

    bool maxNormal;
    QPoint startPos;
    QPoint clickPos;
};

#endif // QTITLEBAREX_H
