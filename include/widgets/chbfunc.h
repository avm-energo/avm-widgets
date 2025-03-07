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

    template <typename T, std::enable_if_t<std::is_unsigned_v<T> || std_ext::is_container<T>::value, bool> = true>
    static bool GroupData(const QWidget *parent, const QString &chbname, T &data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(chbname);
        if (checkBoxGroup == nullptr)
            return false;
        data = checkBoxGroup->bits<std::remove_reference_t<decltype(data)>>();
        return true;
    }

    static bool SetData(QWidget *parent, const QString &chbname, bool data);

    template <typename T, std::enable_if_t<std::is_unsigned_v<T> || std_ext::is_container<T>::value, bool> = true>
    static bool SetGroupData(const QWidget *parent, const QString &name, const T data)
    {
        auto checkBoxGroup = parent->findChild<CheckBoxGroup *>(name);
        if (checkBoxGroup == nullptr)
        {
            qDebug() << name;
            qDebug() << parent->findChildren<QWidget *>();
            return false;
        }
        checkBoxGroup->setBits(data);
        return true;
    }
};
