#pragma once

#include <QCheckBox>
#include <bitset>
#include <gen/std_ext.h>
#include <widgets/export.h>

#define BITSET_MAX_COUNT 32

class WD_EXPORT CheckBoxGroup : public QWidget
{
    Q_OBJECT

public:
    CheckBoxGroup(const QStringList &desc, const QList<int> &ignorePos, QWidget *parent = nullptr);
    CheckBoxGroup(const QStringList &desc, QWidget *parent = nullptr);
    CheckBoxGroup(const QStringList &desc, int count, QWidget *parent = nullptr);
    ~CheckBoxGroup() override;

    template <typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true> void setUBits(const T &value)
    {
        m_bitset = std::bitset<BITSET_MAX_COUNT>(value);
        auto checkBoxes = findChildren<QCheckBox *>();
        for (QCheckBox *checkBox : checkBoxes)
        {
            auto status = false;
            auto number = checkBox->objectName().toUInt(&status);
            if (!status)
                continue;
            checkBox->setChecked(m_bitset.test(number));
        }
    }

    template <typename T, std::enable_if_t<std_ext::is_container<T>::value, bool> = true> void setABits(const T &arr)
    {
        QList<QCheckBox *> checkBoxes = findChildren<QCheckBox *>();
        for (QCheckBox *checkBox : checkBoxes)
        {
            bool status = false;
            auto number = checkBox->objectName().toUInt(&status);
            if (!status)
                continue;
            if (number < arr.size())
                checkBox->setChecked(arr.at(number));
        }
    }

    template <typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true> T uBits()
    {
        const T value = m_bitset.to_ulong();
        return value;
    }

    template <typename T, std::enable_if_t<std_ext::is_container<T>::value, bool> = true> T aBits()
    {
        T arr;
        QList<QCheckBox *> checkBoxes = findChildren<QCheckBox *>();
        for (QCheckBox *checkBox : checkBoxes)
        {
            bool status = false;
            auto number = checkBox->objectName().toUInt(&status);
            if (!status)
                continue;
            if (number < arr.size())
                arr[number] = checkBox->isChecked();
        }
        return arr;
    }

    QList<int> ignorePositions() const
    {
        return m_hiddenPositions;
    }

    bool test(size_t i) const
    {
        return m_bitset.test(i);
    }

    void flip(size_t i)
    {
        m_bitset.flip(i);
    }

    QStringList description() const
    {
        return m_description;
    }

    void setDescription(const QStringList &description)
    {
        m_description = description;
    }

    void setHiddenPositions(const QList<int> &hiddenPositions)
    {
        m_hiddenPositions = hiddenPositions;
    }

protected:
private:
    QList<int> m_hiddenPositions;
    std::bitset<BITSET_MAX_COUNT> m_bitset; // checkbox group maximum items size is 32
    QStringList m_description;
};
