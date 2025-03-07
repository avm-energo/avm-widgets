#pragma once

#include <QLabel>
#include <widgets/export.h>

class WD_EXPORT LBLFunc
{
public:
    LBLFunc();

    [[nodiscard]] static QLabel *New(QWidget *parent, const QString &text, const QString &lblname = "",
        const QPixmap *pm = nullptr, const QString &lbltip = "");
    [[nodiscard]] static QLabel *NewT(QWidget *parent, const QString &text, const QString &lblname = "",
        const QString &lbltip = "", bool fixed = false);
    [[nodiscard]] static QWidget *NewLBL(QWidget *parent, QString lblname, QString caption, bool enabled = false);

    static bool SetImage(QWidget *parent, const QString &lblname, QPixmap *pm);
    static bool SetColor(QWidget *parent, const QString &lblname, const QString &lblcolor);
    static bool SetTColor(QWidget *parent, const QString &lblname, const QString &color);
    static bool SetText(QWidget *parent, const QString &lblname, const QString &lbltext = "", bool enabled = true);
    [[nodiscard]] static QString Text(QWidget *parent, const QString &lblname);
};
