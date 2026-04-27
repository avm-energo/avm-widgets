#include <avm-widgets/emessagebox.h>
#include <avm-widgets/epasswordpopup.h>
#include <avm-widgets/lblfunc.h>

bool EMessageBox::m_result = false;
QByteArray EMessageBox::m_hash = "d93fdd6d1fb5afcca939fa650b62541d09dbcb766f41c39352dc75f348fb35dc";

void EMessageBox::setHash(const QByteArray &ba)
{
    m_hash = ba;
}

bool EMessageBox::password(QWidget *parent, const QString &hash)
{
    m_result = false;
    auto popup = new EPasswordPopup(hash, parent);
    QObject::connect(popup, &EPasswordPopup::passwordIsCorrect, [] { m_result = true; });
    popup->exec();
    return m_result;
}

void EMessageBox::information(QWidget *parent, const QString &msg)
{
    m_result = false;
    auto popup = new EPopup(EPopup::INFOMESSAGE, msg, parent);
    popup->exec();
}

bool EMessageBox::question(QWidget *parent, const QString &msg)
{
    m_result = false;
    auto popup = new EPopup(EPopup::QUESTMSG, msg, parent);
    QObject::connect(popup, &EPopup::accepted, [] { m_result = true; });
    QObject::connect(popup, &EPopup::cancelled, [] { m_result = false; });
    popup->exec();
    return m_result;
}

void EMessageBox::warning(QWidget *parent, const QString &msg)
{
    m_result = false;
    auto popup = new EPopup(EPopup::WARNMESSAGE, LBLFunc::New(parent, msg), parent);
    popup->exec();
}

void EMessageBox::error(QWidget *parent, const QString &msg)
{
    m_result = false;
    auto popup = new EPopup(EPopup::ERMESSAGE, msg, parent);
    popup->setWindowFlag(Qt::WindowStaysOnTopHint, true);
    popup->exec();
}

bool EMessageBox::next(QWidget *parent, const QString &msg)
{
    m_result = false;
    auto popup = new EPopup(EPopup::NEXTMSG, msg, parent);
    QObject::connect(popup, &EPopup::accepted, [&] { m_result = true; });
    QObject::connect(popup, &EPopup::cancelled, [&] { m_result = false; });
    popup->exec();
    return m_result;
}

bool EMessageBox::next(QWidget *parent, QWidget *w)
{
    m_result = false;
    auto popup = new EPopup(EPopup::NEXTMSG, w, parent);
    QObject::connect(popup, &EPopup::accepted, [] { m_result = true; });
    QObject::connect(popup, &EPopup::cancelled, [] { m_result = false; });
    popup->exec();
    return m_result;
}

bool EMessageBox::editableNext(EEditablePopup *popup)
{
    m_result = false;
    QObject::connect(popup, &EPopup::accepted, [] { m_result = true; });
    QObject::connect(popup, &EPopup::cancelled, [] { m_result = false; });
    popup->execPopup();
    return m_result;
}

void EMessageBox::infoWithoutButtons(QWidget *parent, const QString &msg)
{
    auto dlg = new EPopup(EPopup::WITHOUTANYBUTTONS, msg, parent);
    dlg->exec();
}
