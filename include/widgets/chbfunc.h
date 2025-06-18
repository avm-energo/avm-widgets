#pragma once

#include <QCheckBox>
#include <gen/std_ext.h>
#include <widgets/checkboxgroup.h>
#include <widgets/export.h>

class WD_EXPORT ChBFunc
{
public:
    [[nodiscard]] static QCheckBox *New(QWidget *parent, const QString &chbname, const QString &chbtext);
    [[nodiscard]] static QWidget *NewLBL(
        QWidget *parent, const QString &caption, const QString &chbname, const QString &chbtext);
    static bool Data(const QWidget *parent, const QString &chbname, bool &data);
    static bool Data(const QWidget *parent, const QString &chbname);

    template <typename T> static bool Data(const QWidget *parent, const QString &chbname, T &data)
    {
        auto chb = parent->findChild<QCheckBox *>(chbname);
        if (chb == nullptr)
            return false;
        data = chb->isChecked();
        return true;
    }

    template<typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
    static bool uGroupData(const QWidget *parent, const QString &chbname, T &data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(chbname);
        if (checkBoxGroup == nullptr)
            return false;
        data = checkBoxGroup->uBits<T>();
        return true;
    }

    template<typename T, std::enable_if_t<std_ext::is_container<T>::value, bool> = true>
    static bool aGroupData(const QWidget *parent, const QString &chbname, T &data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(chbname);
        if (checkBoxGroup == nullptr)
            return false;
        data = checkBoxGroup->aBits<T>();
        return true;
    }

    static bool SetData(QWidget *parent, const QString &chbname, bool data);

    template<typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
    static bool SetUGroupData(const QWidget *parent, const QString &name, const T data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(name);
        if (checkBoxGroup == nullptr)
        {
            qDebug() << name;
            qDebug() << parent->findChildren<QWidget *>();
            return false;
        }
        checkBoxGroup->setUBits(data);
        return true;
    }

    template<typename T, std::enable_if_t<std_ext::is_container<T>::value, bool> = true>
    static bool SetAGroupData(const QWidget *parent, const QString &name, const T data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(name);
        if (checkBoxGroup == nullptr) {
            qDebug() << name;
            qDebug() << parent->findChildren<QWidget *>();
            return false;
        }
        checkBoxGroup->setABits(data);
        return true;
    }
};
