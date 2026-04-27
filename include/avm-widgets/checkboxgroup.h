#pragma once

#include <QCheckBox>
#include <bitset>
#include <avm-gen/std_ext.h>
#include <export.h>

inline constexpr int BITSET_MAX_COUNT = 32;

/// \brief A widget containing a group of checkboxes laid out using FlowLayout,
///        backed by a bitset for fast bit-level access.
class WD_EXPORT CheckBoxGroup : public QWidget
{
    Q_OBJECT

public:
    /// \brief Constructs a group using \a desc as labels, hiding positions listed in \a ignorePos.
    CheckBoxGroup(const QStringList &desc, const QList<int> &ignorePos, QWidget *parent = nullptr);
    /// \brief Constructs a group using \a desc as labels, all positions visible.
    CheckBoxGroup(const QStringList &desc, QWidget *parent = nullptr);
    /// \brief Constructs a group with exactly \a count checkboxes labelled by \a desc.
    CheckBoxGroup(const QStringList &desc, int count, QWidget *parent = nullptr);
    ~CheckBoxGroup() override = default;

    /// \brief Sets checkbox states from the bits of the unsigned integer \a value.
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

    /// \brief Sets checkbox states from a container \a arr where each element is treated as bool.
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

    /// \brief Returns the current checkbox states as an unsigned integer (bit-packed).
    template <typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true> T uBits()
    {
        const T value = m_bitset.to_ulong();
        return value;
    }

    /// \brief Returns the current checkbox states as a container of bool-like elements.
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

    /// \brief Returns the list of checkbox positions that are hidden.
    QList<int> ignorePositions() const
    {
        return m_hiddenPositions;
    }

    /// \brief Returns true if bit \a i is set in the internal bitset.
    bool test(size_t i) const
    {
        return m_bitset.test(i);
    }

    /// \brief Flips bit \a i in the internal bitset.
    void flip(size_t i)
    {
        m_bitset.flip(i);
    }

    /// \brief Returns the label strings for all checkboxes.
    QStringList description() const
    {
        return m_description;
    }

    /// \brief Sets the label strings; does not recreate the checkboxes.
    void setDescription(const QStringList &description)
    {
        m_description = description;
    }

    /// \brief Sets the list of hidden checkbox positions.
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
