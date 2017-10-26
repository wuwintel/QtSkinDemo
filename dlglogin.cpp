#include "dlglogin.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMessageBox>

DlgLogin::DlgLogin(QWidget *parent)
    : QDialog(parent)
{
    // username
    QLabel *usrTitle = new QLabel(tr("用户名:"));
    usrTitle->setMinimumWidth(60);
    usrTitle->setMaximumWidth(60);

    m_usrEditor = new QLineEdit();
    m_usrEditor->setPlaceholderText(tr("请输入用户名"));
    m_usrEditor->setMaximumWidth(160);

    QHBoxLayout *hUsrBox = new QHBoxLayout;
    hUsrBox->setAlignment(Qt::AlignCenter);
    hUsrBox->addWidget(usrTitle);
    hUsrBox->addWidget(m_usrEditor);

    // password
    QLabel *pwdTitle = new QLabel(tr("密码:"));
    pwdTitle->setMinimumWidth(60);
    pwdTitle->setMaximumWidth(60);

    m_pwdEditor = new QLineEdit();
    m_pwdEditor->setPlaceholderText(tr("请输入密码"));
    m_pwdEditor->setMaximumWidth(160);
    m_pwdEditor->setEchoMode(QLineEdit::Password);  //密码输入模式

    QHBoxLayout *hPwdBox = new QHBoxLayout;
    hPwdBox->setAlignment(Qt::AlignCenter);
    hPwdBox->addWidget(pwdTitle);
    hPwdBox->addWidget(m_pwdEditor);

    // push button
    QPushButton *btnLogin = new QPushButton(tr("登录"));
    btnLogin->setMinimumWidth(80);
    btnLogin->setMaximumWidth(80);

    QPushButton *btnCancel = new QPushButton(tr("取消"));
    btnCancel->setMinimumWidth(80);
    btnCancel->setMaximumWidth(80);

    QHBoxLayout *hBtnBox = new QHBoxLayout;
    hBtnBox->addWidget(btnLogin);
    hBtnBox->addWidget(btnCancel);

    //  内部所用部件
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addStretch(3);
    vbox->addLayout(hUsrBox);
    vbox->addStretch(1);
    vbox->addLayout(hPwdBox);
    vbox->addStretch(3);
    vbox->addLayout(hBtnBox);
    vbox->addStretch(3);

    // 添加一个外框
    QGroupBox *pGrpBox = new QGroupBox;
    pGrpBox->setMinimumSize(320, 240);
    pGrpBox->setMaximumSize(320, 240);
    pGrpBox->setLayout(vbox);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(pGrpBox);
    mainLayout->setAlignment(Qt::AlignCenter);

    // 设置布局
    this->setLayout(mainLayout);

    QObject::connect(btnLogin, SIGNAL(clicked(bool)), this, SLOT(login()));
    QObject::connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

DlgLogin::~DlgLogin()
{

}

void DlgLogin::login()
{
    if(m_usrEditor->text().trimmed() == "Admin" && m_pwdEditor->text()==("123456"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("用户名或密码错误!"), QMessageBox::Yes);
        cancel();
    }
}

void DlgLogin::cancel()
{
    // 清空内容并重置光标
    m_usrEditor->clear();
    m_pwdEditor->clear();
    m_usrEditor->setFocus();
}
