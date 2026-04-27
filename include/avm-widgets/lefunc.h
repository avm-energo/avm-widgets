#pragma once

#include <QHBoxLayout>
#include <QLineEdit>
#include <avm-widgets/passwordlineedit.h>
#include <export.h>

/// \brief Factory and accessor helpers for QLineEdit and PasswordLineEdit widgets.
class WD_EXPORT LEFunc
{
public:
    /// \brief Finds a QLineEdit by \a lename inside \a parent.
    [[nodiscard]] static QLineEdit *lineEdit(QWidget *parent, const QString &lename);
    /// \brief Creates a new QLineEdit with initial text \a letext and tooltip \a tooltip.
    [[nodiscard]] static QLineEdit *New(
        QWidget *parent, const QString &lename, const QString &letext = "", const QString &tooltip = "");
    /// \brief Creates a PasswordLineEdit (line edit + show/hide toggle button) with echo mode \a echostyle.
    [[nodiscard]] static PasswordLineEdit *newPsw(
        QWidget *parent, const QString &lename, QLineEdit::EchoMode echostyle = QLineEdit::Password);
    /// \brief Sets the text of a line edit found by \a lename; optionally validates against \a restring regex.
    static bool setData(QObject *parent, const QString &lename, const QString &levalue, const QString &restring = "");
    /// \brief Returns the current text of a line edit found by \a lename.
    [[nodiscard]] static QString data(QObject *parent, const QString &lename);

    /// \brief Reads the line edit text and converts it to \a T via QVariant.
    template <typename T> static void data(QObject *parent, const QString &lename, T &value)
    {
        auto le = parent->findChild<QLineEdit *>(lename);
        if (le == nullptr)
            value = T();
        else
            value = qvariant_cast<T>(le->text());
    }

    /// \brief Reads the line edit text as a double and stores it in \a levalue.
    template <typename T> static bool number(QWidget *parent, const QString &lename, T &levalue)
    {
        auto le = parent->findChild<QLineEdit *>(lename);
        if (le == nullptr)
            return false;
        levalue = le->text().toDouble();
        return true;
    }

    /// \brief Sets the background color of a line edit found by \a lename.
    static bool setColor(QWidget *parent, const QString &lename, const QColor &color);

    /// \brief Creates a caption label + line edit pair widget.
    [[nodiscard]] static QWidget *newLBL(QWidget *parent, QString caption, QString lename, bool enabled = false);
    /// \brief Creates a caption label + password line edit pair widget.
    [[nodiscard]] static QWidget *newPswLBL(QWidget *parent, QString caption, QString lename);
};
