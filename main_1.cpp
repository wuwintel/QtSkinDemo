#include <QApplication>
#include <QFile>
#include <QLabel>

void LoadSkin(const QString &style)
{
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLabel hello("Hello world", NULL);
    hello.show();

    LoadSkin(":/res/qss/drak_01.qss");

    return a.exec();
}
