#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QTranslator>
#include <QInputDialog>
#include <QMessageBox>

#include "qtitlebarex.h"
#include "dlglogin.h"

QTranslator g_trans;//必须设置成全局变量，如果是局部变量，设置将失效。
void setLanguage(int lan)//全局函数，可供其他文件调用
{
    bool ok = false;
    if (lan == 1)//中文
    {
        ok = g_trans.load("qt_zh_CN.qm", ":/lan/");//这里使用Qt资源文件,把.qm文件拷贝到项目路径/lan之下
    }
    else if (lan == 2)//英文
    {
        ok = g_trans.load("", ":/lan/");
    }

    QCoreApplication::installTranslator(&g_trans);
    //或者写成qApp->installTranslator(&g_trans);
}


void LoadSkin(const QString &style)
{
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

const QString strSkin(":/res/qss/qdarkstyle/qdarkstyle.qss");
//const QString strSkin(":/res/qss/darkorange.qss");
//const QString strSkin(":/res/qss/white_01.qss");
//const QString strSkin(":/res/qss/skin_03.qss");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置编码格式
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    // 设置语言
    setLanguage(1);

    // 加载皮肤
    LoadSkin(strSkin);

 #if 1
    bool isOK;
    QString text = QInputDialog::getText(NULL, "Input Dialog", "Please input your comment",
                                         QLineEdit::Normal, "your comment", &isOK);
    if(isOK)
    {
        QMessageBox::information(NULL, "Information", "Your comment is: <b>" + text + "</b>",
                                 QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    }

    MainWindow w;

    DlgLogin dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        w.resize(800, 600);
        w.show();
        return a.exec();
    }
 #endif

    //a.exec();

    return 0;
}
