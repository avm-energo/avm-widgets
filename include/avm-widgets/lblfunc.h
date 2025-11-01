#pragma once

#include <avm-widgets/elabel.h>
#include <export.h>

class WD_EXPORT LBLFunc
{
public:
    LBLFunc();

    [[nodiscard]] static ELabel *New(QWidget *parent, const QString &text, const QString &lblname = "",
        const QPixmap *pm = nullptr, const QString &lbltip = "");
    [[nodiscard]] static ELabel *newT(QWidget *parent, const QString &text, const QString &lblname = "",
        const QString &lbltip = "", bool fixed = false);
    [[nodiscard]] static QWidget *newLBL(QWidget *parent, QString lblname, QString caption, bool enabled = false);

    static bool setImage(QWidget *parent, const QString &lblname, QPixmap *pm);
    static bool setColor(QWidget *parent, const QString &lblname, const QString &lblcolor);
    static bool setBGColor(QWidget *parent, const QString &lblname, const QString &color);
    static bool setText(QWidget *parent, const QString &lblname, const QString &lbltext = "", bool enabled = true);
    [[nodiscard]] static QString text(QWidget *parent, const QString &lblname);
    static bool setData(QWidget *parent, const QString &lblname, const QString &data);
    [[nodiscard]] static QString data(QWidget *parent, const QString &lblname);
};
