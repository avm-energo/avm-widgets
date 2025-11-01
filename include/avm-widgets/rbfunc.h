#pragma once

#include <QRadioButton>
#include <export.h>

class WD_EXPORT RBFunc
{
public:
    [[nodiscard]] static QRadioButton *New(QWidget *parent, const QString &rbtext, const QString &rbname);
    [[nodiscard]] static QWidget *newLBL(
        QWidget *parent, const QString &caption, const QString &rbtext, const QString &rbname);
    static bool data(QWidget *parent, const QString &rbname, bool &data);
    static bool setData(QWidget *parent, const QString &rbname, bool data);
};
