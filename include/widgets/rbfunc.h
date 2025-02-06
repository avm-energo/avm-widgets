#pragma once

#include <QRadioButton>
#include <widgets/export.h>

class WD_EXPORT RBFunc
{
public:
    RBFunc();

    [[nodiscard]] static QRadioButton *NewRB2(QWidget *parent, const QString &rbtext, const QString &rbname);
    static bool RBData(QWidget *parent, const QString &rbname, bool &data);
    static bool SetRBData(QWidget *parent, const QString &rbname, bool data);
};
