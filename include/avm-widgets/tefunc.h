#pragma once

#include <QTextEdit>
#include <export.h>

/// \brief Factory and accessor helpers for QTextEdit widgets.
class WD_EXPORT TEFunc
{
public:
    /// \brief Finds a QTextEdit by \a tename inside \a parent.
    static QTextEdit *textedit(QWidget *parent, const QString &tename);
    /// \brief Creates a new read-only QTextEdit.
    static QTextEdit *New(QWidget *parent, const QString &tename);
    /// \brief Appends \a tetext to the text edit found by \a tename.
    static bool appendData(QWidget *parent, const QString &tename, const QString &tetext);
    /// \brief Replaces the full content of the text edit found by \a tename with \a tetext.
    static bool setData(QWidget *parent, const QString &tename, const QString &tetext);
    /// \brief Returns the plain text content of the text edit found by \a tename into \a tevalue.
    static bool data(QWidget *parent, const QString &tename, QString &tevalue);
};
