#pragma once

#include <QRadioButton>
#include <export.h>

/// \brief Factory and accessor helpers for QRadioButton widgets.
class WD_EXPORT RBFunc
{
public:
    /// \brief Finds a QRadioButton by \a rbname inside \a parent.
    [[nodiscard]] static QRadioButton *radioButton(QWidget *parent, const QString &rbname);
    /// \brief Creates a new QRadioButton with label \a rbtext.
    [[nodiscard]] static QRadioButton *New(QWidget *parent, const QString &rbtext, const QString &rbname);
    /// \brief Creates a caption label + radio button pair widget.
    [[nodiscard]] static QWidget *newLBL(
        QWidget *parent, const QString &caption, const QString &rbtext, const QString &rbname);
    /// \brief Reads the checked state of the radio button found by \a rbname into \a data.
    static bool data(QWidget *parent, const QString &rbname, bool &data);
    /// \brief Sets the checked state of the radio button found by \a rbname.
    static bool setData(QWidget *parent, const QString &rbname, bool data);
};
