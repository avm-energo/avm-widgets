#pragma once

#include <QString>
#include <export.h>

class QMainWindow;
class QWidget;
class WD_EXPORT WDFunc
{
public:
    WDFunc();
    static void setEnabled(QWidget *w, const QString &wname, bool enabled);
    static void setVisible(QWidget *w, const QString &wname, bool visible);
    static bool floatIsWithinLimits(const QString &varname, double var, double base, double tolerance);
    [[nodiscard]] static QString stringFloatValueWithCheck(float value, int precision = 5, bool exp = false);
    [[nodiscard]] static QMainWindow *getMainWindow();
};
