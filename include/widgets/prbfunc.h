#pragma once

#include <QProgressBar>
#include <widgets/export.h>

class WD_EXPORT PrbFunc
{
public:
    [[nodiscard]] static QProgressBar *New(QWidget *parent, const QString &prbname);
    [[nodiscard]] static QWidget *NewLBL(QWidget *parent, const QString &caption, const QString &prbname);
    static bool setRange(QWidget *parent, const QString &prbname, qint64 value);
    static bool setValue(QWidget *parent, const QString &prbname, qint64 value);
};
