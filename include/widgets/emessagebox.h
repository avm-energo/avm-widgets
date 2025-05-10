#pragma once

#include <QWidget>
#include <widgets/eeditablepopup.h>
#include <widgets/export.h>

class WD_EXPORT EMessageBox
{
public:
    static bool m_result;
    static QByteArray m_hash;
    static void setHash(const QByteArray &ba);
    static bool password(QWidget *parent, const QString &hash = m_hash);
    static void information(QWidget *parent, const QString &msg);
    static bool question(QWidget *parent, const QString &msg); // yes (1) / no (0)
    static void warning(QWidget *parent, const QString &msg);
    static void error(QWidget *parent, const QString &msg);
    static bool next(QWidget *parent, const QString &msg); // next (1) / cancel (0)
    static bool next(QWidget *parent, QWidget *w);         // next (1) / cancel (0)
    static bool editableNext(EEditablePopup *popup);
    static void infoWithoutButtons(QWidget *parent, const QString &msg); // timeout to close dialog in seconds
};
