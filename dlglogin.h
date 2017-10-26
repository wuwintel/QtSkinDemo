#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>


class QLineEdit;

class DlgLogin : public QDialog
{
    Q_OBJECT

public:
    DlgLogin(QWidget *parent = 0);
    ~DlgLogin();

private slots:
    void login();
    void cancel();

private:
    QLineEdit *m_usrEditor;
    QLineEdit *m_pwdEditor;
};

#endif // DLGLOGIN_H
