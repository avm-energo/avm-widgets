#include "widgets/epopup.h"

#include <QKeyEvent>
#include <QVBoxLayout>
#include <widgets/graphfunc.h>
#include <widgets/lblfunc.h>
#include <widgets/lefunc.h>
#include <widgets/passwordlineedit.h>
#include <widgets/pbfunc.h>

EPopup::EPopup(QWidget *parent) : QDialog(parent)
{
}

EPopup::EPopup(MessageTypes type, const QString &msg, QWidget *parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowModality(Qt::WindowModal);
    setStyleSheet("QFrame {border-radius: 10px; border: 3px solid gray;}");
    Create(type, LBLFunc::New(parent, msg), parent);
}

EPopup::EPopup(MessageTypes type, QWidget *w, QWidget *parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowModality(Qt::WindowModal);
    setStyleSheet("QFrame {border-radius: 10px; border: 3px solid gray;}");
    Create(type, w, parent);
}

void EPopup::Create(MessageTypes &type, QWidget *w, QWidget *parent)
{
    struct msgsStruct
    {
        QString pxFile;
        QString bgrdColor;
    };

    QMap<MessageTypes, msgsStruct> map = {
        { INFOMESSAGE, { ":/icons/info-hex.svg", "c8fcff" } },
        { WARNMESSAGE, { ":/icons/warn-hex.svg", "ffffc3" } },
        { QUESTMSG, { ":/icons/question-hex.svg", "b5b6ff" } },
        { ERMESSAGE, { ":/icons/err-hex.svg", "ffd4d4" } },
        { NEXTMSG, { ":/icons/next-hex.svg", "d6ffce" } },
        { WITHOUTANYBUTTONS, { ":/icons/ordinary-hex.svg", "f3ffc5" } },
    };
    setAttribute(Qt::WA_DeleteOnClose);
    setStyleSheet("QDialog {background-color: #" + map[type].bgrdColor + ";}");
    w->setStyleSheet("QWidget {background-color: #" + map[type].bgrdColor + ";}");
    if (type < c_captions.size())
        setWindowTitle(c_captions.at(type));
    QVBoxLayout *lyout = new QVBoxLayout;
    QHBoxLayout *hlyout = new QHBoxLayout;

    auto icon = GraphFunc::NewIcon(parent, map[type].pxFile);
    icon->setStyleSheet("QWidget {background-color: #" + map[type].bgrdColor + ";}");
    hlyout->addWidget(icon);
    hlyout->addWidget(w);
    lyout->addLayout(hlyout);
    hlyout = new QHBoxLayout;
    hlyout->addStretch(100);
    if (type == EPopup::QUESTMSG)
    {
        hlyout->addWidget(PBFunc::New(parent, "", "Да", this, &EPopup::acceptSlot));
        hlyout->addStretch(5);
        hlyout->addWidget(PBFunc::New(parent, "", "Нет", this, &EPopup::cancelSlot));
    }
    else if (type == EPopup::NEXTMSG)
    {
        hlyout->addWidget(PBFunc::New(parent, "", "Далее", this, &EPopup::acceptSlot));
        hlyout->addStretch(5);
        hlyout->addWidget(PBFunc::New(parent, "", "Отмена", this, &EPopup::cancelSlot));
    }
    else if (type != EPopup::WITHOUTANYBUTTONS)
        hlyout->addWidget(PBFunc::New(parent, "", "Далее", [&] { this->aboutToClose(); }));
    hlyout->addStretch(100);
    lyout->addLayout(hlyout);
    setLayout(lyout);
    this->adjustSize();
}

void EPopup::aboutToClose()
{
    close();
}

void EPopup::showEvent(QShowEvent *e)
{
    QDialog::showEvent(e);
}

void EPopup::closeEvent(QCloseEvent *e)
{
    emit closed();
    QDialog::closeEvent(e);
}

void EPopup::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        cancelSlot();
    if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
        acceptSlot();
}

void EPopup::acceptSlot()
{
    emit accepted();
    aboutToClose();
}

void EPopup::cancelSlot()
{
    emit cancelled();
    aboutToClose();
}
