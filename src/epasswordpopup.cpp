#include <QCryptographicHash>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <widgets/emessagebox.h>
#include <widgets/epasswordpopup.h>
#include <widgets/graphfunc.h>
#include <widgets/lblfunc.h>
#include <widgets/lefunc.h>
#include <widgets/styleloader.h>

EPasswordPopup::EPasswordPopup(const QString &hash, QWidget *parent) : EPopup(parent)
{
    QString backgroundColor = (StyleLoader::styleName().compare("Dark") ? "ffe3f9" : "b6008f");
    QString dialogStyle = "QDialog { background-color: #" + backgroundColor + "};";
    QString widgetStyle = "QWidget { background-color: #" + backgroundColor + " }";
    isAboutToClose = false;
    m_hash = hash;
    QHBoxLayout *hlyout = new QHBoxLayout;
    auto icon = GraphFunc::NewIcon(parent, ":/icons/psw-hex.svg");
    icon->setStyleSheet(widgetStyle);
    hlyout->addWidget(icon);
    auto text = LBLFunc::New(this, "Введите пароль\nПодтверждение: клавиша Enter\nОтмена: клавиша Esc", "pswlbl");
    text->setStyleSheet(widgetStyle);
    hlyout->addWidget(text);
    QVBoxLayout *vlyout = new QVBoxLayout;
    vlyout->addLayout(hlyout);
    vlyout->addWidget(LEFunc::NewPsw(this, "pswle", QLineEdit::Password));
    setLayout(vlyout);
    adjustSize();
    setStyleSheet(dialogStyle);
}

bool EPasswordPopup::checkPassword(const QString &password)
{
    QCryptographicHash hasher(QCryptographicHash::Sha3_256);
    hasher.addData(password.toUtf8());
    auto buffer = QString::fromUtf8(hasher.result().toHex());
    return (m_hash == buffer);
}

void EPasswordPopup::keyPressEvent(QKeyEvent *e)
{
    if ((e->modifiers() == Qt::AltModifier) || (e->modifiers() == Qt::ControlModifier))
    {
        qCritical("Ошибка при обработке пароля");
        return;
    }

    if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
    {
        if (checkPassword(LEFunc::Data(this, "pswle")))
        {
            emit passwordIsCorrect();
            aboutToClose();
        }
        else
        {
            qCritical("Пароль введён неверно");
            EMessageBox::warning(this, "Пароль неверен");
        }
    }
    if ((e->key() == Qt::Key_Escape) && !isAboutToClose)
    {
        isAboutToClose = true;
        EPopup::cancelSlot();
    }
    QDialog::keyPressEvent(e);
}

void EPasswordPopup::closeEvent(QCloseEvent *e)
{
    EPopup::closeEvent(e);
}
