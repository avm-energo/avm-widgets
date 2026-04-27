#pragma once

#include <QCheckBox>
#include <avm-widgets/checkboxgroup.h>
#include <export.h>
#include <avm-gen/std_ext.h>

/// \brief Factory and accessor helpers for QCheckBox and CheckBoxGroup widgets.
class WD_EXPORT ChBFunc
{
public:
    /// \brief Finds a QCheckBox by \a chbname inside \a parent.
    [[nodiscard]] static QCheckBox *checkBox(QWidget *parent, const QString &chbname);
    /// \brief Creates a new QCheckBox with label \a chbtext.
    [[nodiscard]] static QCheckBox *New(QWidget *parent, const QString &chbname, const QString &chbtext);
    /// \brief Creates a caption label + checkbox pair widget.
    [[nodiscard]] static QWidget *newLBL(
        QWidget *parent, const QString &caption, const QString &chbname, const QString &chbtext);
    /// \brief Reads the checked state of the checkbox found by \a chbname into \a data.
    static bool data(const QWidget *parent, const QString &chbname, bool &data);
    /// \brief Returns the checked state of the checkbox found by \a chbname (false if not found).
    static bool data(const QWidget *parent, const QString &chbname);

    /// \brief Reads the checked state into \a data converted to \a T (e.g. int, bool).
    template <typename T> static bool data(const QWidget *parent, const QString &chbname, T &data)
    {
        auto chb = parent->findChild<QCheckBox *>(chbname);
        if (chb == nullptr)
            return false;
        data = chb->isChecked();
        return true;
    }

    /// \brief Reads the unsigned bit-packed value of a CheckBoxGroup into \a data.
    template <typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
    static bool uGroupData(const QWidget *parent, const QString &chbname, T &data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(chbname);
        if (checkBoxGroup == nullptr)
            return false;
        data = checkBoxGroup->uBits<T>();
        return true;
    }

    /// \brief Reads the container-encoded state of a CheckBoxGroup into \a data.
    template <typename T, std::enable_if_t<std_ext::is_container<T>::value, bool> = true>
    static bool aGroupData(const QWidget *parent, const QString &chbname, T &data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(chbname);
        if (checkBoxGroup == nullptr)
            return false;
        data = checkBoxGroup->aBits<T>();
        return true;
    }

    /// \brief Sets the checked state of the checkbox found by \a chbname.
    static bool setData(QWidget *parent, const QString &chbname, bool data);

    /// \brief Sets a CheckBoxGroup from the bits of the unsigned integer \a data.
    template <typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
    static bool setUGroupData(const QWidget *parent, const QString &name, const T data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(name);
        if (checkBoxGroup == nullptr)
        {
            qWarning() << "CheckBoxGroup not found:" << name;
            return false;
        }
        checkBoxGroup->setUBits(data);
        return true;
    }

    /// \brief Sets a CheckBoxGroup from a container \a data of bool-like values.
    template <typename T, std::enable_if_t<std_ext::is_container<T>::value, bool> = true>
    static bool setAGroupData(const QWidget *parent, const QString &name, const T data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(name);
        if (checkBoxGroup == nullptr)
        {
            qWarning() << "CheckBoxGroup not found:" << name;
            return false;
        }
        checkBoxGroup->setABits(data);
        return true;
    }
};
