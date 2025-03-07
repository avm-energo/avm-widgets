#pragma once

#include <QRadioButton>
#include <widgets/export.h>

class WD_EXPORT RBFunc
{
public:
    [[nodiscard]] static QRadioButton *New(QWidget *parent, const QString &rbtext, const QString &rbname);
    [[nodiscard]] static QWidget *NewLBL(
        QWidget *parent, const QString &caption, const QString &rbtext, const QString &rbname);
    static bool Data(QWidget *parent, const QString &rbname, bool &data);
    static bool SetData(QWidget *parent, const QString &rbname, bool data);
};
