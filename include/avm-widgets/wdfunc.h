#pragma once

#include <QString>
#include <export.h>

class QMainWindow;
class QWidget;
/// \brief General-purpose widget utility functions.
class WD_EXPORT WDFunc
{
public:
    WDFunc();
    /// \brief Enables or disables the child widget named \a wname inside \a w.
    static void setEnabled(QWidget *w, const QString &wname, bool enabled);
    /// \brief Shows or hides the child widget named \a wname inside \a w.
    static void setVisible(QWidget *w, const QString &wname, bool visible);
    /// \brief Returns true if \a var is within \a base ± \a tolerance; logs an error and shows a dialog otherwise.
    static bool floatIsWithinLimits(const QString &varname, double var, double base, double tolerance);
    /// \brief Formats \a value as a string with \a precision digits; returns "***" for infinite/NaN values.
    [[nodiscard]] static QString stringFloatValueWithCheck(float value, int precision = 5, bool exp = false);
    /// \brief Returns the first QMainWindow found among top-level widgets, or nullptr.
    [[nodiscard]] static QMainWindow *getMainWindow();
};
