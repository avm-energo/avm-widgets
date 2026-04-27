#pragma once

#include <QWidget>
#include <avm-widgets/eeditablepopup.h>
#include <export.h>

/// \brief Convenience wrappers around EPopup for common modal dialog types.
class WD_EXPORT EMessageBox
{
public:
    static bool m_result;
    static QByteArray m_hash;
    /// \brief Sets the global default SHA3-256 password hash used by password().
    static void setHash(const QByteArray &ba);
    /// \brief Shows a password dialog and returns true if the entered password matches \a hash.
    static bool password(QWidget *parent, const QString &hash = m_hash);
    /// \brief Shows an information dialog with \a msg.
    static void information(QWidget *parent, const QString &msg);
    /// \brief Shows a yes/no question dialog; returns true for "Yes".
    static bool question(QWidget *parent, const QString &msg);
    /// \brief Shows a warning dialog with \a msg.
    static void warning(QWidget *parent, const QString &msg);
    /// \brief Shows an error dialog with \a msg (always on top).
    static void error(QWidget *parent, const QString &msg);
    /// \brief Shows a "Next / Cancel" dialog with text \a msg; returns true for "Next".
    static bool next(QWidget *parent, const QString &msg);
    /// \brief Shows a "Next / Cancel" dialog embedding widget \a w; returns true for "Next".
    static bool next(QWidget *parent, QWidget *w);
    /// \brief Runs the editable popup \a popup; returns true if the user accepted.
    static bool editableNext(EEditablePopup *popup);
    /// \brief Shows an information dialog with no buttons (must be closed programmatically).
    static void infoWithoutButtons(QWidget *parent, const QString &msg);
};
