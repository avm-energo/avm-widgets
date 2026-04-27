#pragma once

#include <QLineEdit>
#include <export.h>

/// \brief A composite widget consisting of a QLineEdit and a toggle button that switches
///        between Password and Normal echo modes.
class WD_EXPORT PasswordLineEdit : public QWidget
{
    Q_OBJECT

public:
    /// \brief Constructs the widget; \a echostyle sets the initial echo mode.
    explicit PasswordLineEdit(QWidget *parent = Q_NULLPTR,
                              const QString &lename = "",
                              QLineEdit::EchoMode echostyle = QLineEdit::Password);

private slots:
    /// \brief Toggles the echo mode of the line edit identified by \a lename.
    void pswLEToggleEchoMode(const QString &lename);
};
