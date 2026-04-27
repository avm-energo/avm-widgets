#pragma once

#include <QProgressBar>
#include <export.h>

/// \brief Factory and accessor helpers for QProgressBar widgets.
class WD_EXPORT PrbFunc
{
public:
    /// \brief Finds a QProgressBar by \a prbname inside \a parent.
    [[nodiscard]] static QProgressBar *progressBar(QWidget *parent, const QString &prbname);
    /// \brief Creates a new QProgressBar.
    [[nodiscard]] static QProgressBar *New(QWidget *parent, const QString &prbname);
    /// \brief Creates a caption label + progress bar pair widget with optional format string \a format.
    [[nodiscard]] static QWidget *newLBL(
        QWidget *parent, const QString &caption, const QString &prbname, const QString &format = "%p%");
    /// \brief Sets the maximum range of the progress bar to \a value.
    static bool setRange(QWidget *parent, const QString &prbname, qint64 value);
    /// \brief Sets the current value of the progress bar to \a value.
    static bool setValue(QWidget *parent, const QString &prbname, qint64 value);
};
