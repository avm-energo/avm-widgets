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

    template<typename T>
    void setUBits(const T value)
    {
        m_bitset = std::bitset<BITSET_MAX_COUNT>(value);
        auto checkBoxes = findChildren<QCheckBox *>();
        for (QCheckBox *checkBox : checkBoxes) {
            auto status = false;
            auto number = checkBox->objectName().toUInt(&status);
            if (!status)
                continue;
            checkBox->setChecked(m_bitset.test(number));
        }
    }

    template<typename T, std::size_t SIZE>
    void setABits(const std::array<T, SIZE> &arr)
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

    template<typename T>
    T uBits()
    {
        const T value = m_bitset.to_ulong();
        return value;
    }

    template<typename T, std::size_t SIZE>
    std::array<T, SIZE> aBits()
    {
        std::array<T, SIZE> arr;
        QList<QCheckBox *> checkBoxes = findChildren<QCheckBox *>();
        for (QCheckBox *checkBox : checkBoxes) {
            bool status = false;
            auto number = checkBox->objectName().toUInt(&status);
            if (!status)
                continue;
            if (number < arr.size())
                arr[number] = checkBox->isChecked();
        }
        return arr;
    }

    QList<int> ignorePositions() const { return m_hiddenPositions; }

    bool test(size_t i) const { return m_bitset.test(i); }

    void flip(size_t i) { m_bitset.flip(i); }

    QStringList description() const { return m_description; }

    void setDescription(const QStringList &description) { m_description = description; }

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

extern template void CheckBoxGroup::setUBits(const quint64 value);
extern template void CheckBoxGroup::setUBits(const quint32 value);
extern template void CheckBoxGroup::setUBits(const quint16 value);
extern template void CheckBoxGroup::setUBits(const quint8 value);

// extern template quint64 CheckBoxGroup::uBits();
// extern template quint32 CheckBoxGroup::uBits();
// extern template quint16 CheckBoxGroup::uBits();
// extern template quint8 CheckBoxGroup::uBits();
