#pragma once

#include <QHBoxLayout>
#include <QLineEdit>
#include <avm-widgets/passwordlineedit.h>
#include <export.h>

class WD_EXPORT LEFunc
{
public:
    [[nodiscard]] static QLineEdit *New(
        QWidget *parent, const QString &lename, const QString &letext = "", const QString &tooltip = "");
    [[nodiscard]] static PasswordLineEdit *newPsw(
        QWidget *parent, const QString &lename, QLineEdit::EchoMode echostyle = QLineEdit::Password);
    static bool setData(QObject *parent, const QString &lename, const QString &levalue, const QString &restring = "");
    [[nodiscard]] static QString data(QObject *parent, const QString &lename);

    template <typename T> static void data(QObject *parent, const QString &lename, T &value)
    {
        auto le = parent->findChild<QLineEdit *>(lename);
        if (le == nullptr)
            value = T();
        else
            value = qvariant_cast<T>(le->text());
    }

    template <typename T> static bool number(QWidget *parent, const QString &lename, T &levalue)
    {
        auto le = parent->findChild<QLineEdit *>(lename);
        if (le == nullptr)
            return false;
        levalue = le->text().toDouble();
        return true;
    }

    static bool setColor(QWidget *parent, const QString &lename, const QColor &color);

    [[nodiscard]] static QWidget *newLBL(QWidget *parent, QString caption, QString lename, bool enabled = false);
    [[nodiscard]] static QWidget *newPswLBL(QWidget *parent, QString caption, QString lename);
};
