#pragma once

#include <QAbstractSpinBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <avm-widgets/edoublespinbox.h>
#include <avm-widgets/espinbox.h>
#include <avm-widgets/flowlayout.h>

/// \brief A group of spin boxes laid out using FlowLayout.
/// \tparam T  Value type (int, double, etc.)
/// \tparam S  Spin box widget type (must derive from QAbstractSpinBox)
template <typename T, class S, std::enable_if_t<std::is_base_of<QAbstractSpinBox, S>::value, bool> = true>
class BaseSpinBoxGroup : public QWidget
{
private:
    /// \brief Creates a labelled spin-box pair widget.
    [[nodiscard]] QWidget *createWidget(const QString &str)
    {
        QWidget *widget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(new QLabel(str, this), 0, Qt::AlignRight);
        layout->addWidget(new S(this));
        widget->setLayout(layout);
        return widget;
    }

public:
    /// \brief Constructs a group with \a count auto-numbered spin boxes.
    explicit BaseSpinBoxGroup(int count, QWidget *parent = nullptr) : QWidget(parent), m_count(count)
    {
        FlowLayout *flowLayout = new FlowLayout;
        flowLayout->setObjectName("basespinboxgroup");
        for (auto i = 0; i != m_count; ++i)
        {
            flowLayout->addWidget(createWidget(QString::number(i + 1)));
        }
        setLayout(flowLayout);
    }

    /// \brief Constructs a group with labels taken from \a list.
    explicit BaseSpinBoxGroup(const QStringList &list, QWidget *parent = nullptr)
        : QWidget(parent), m_count(list.size())
    {
        FlowLayout *flowLayout = new FlowLayout;
        flowLayout->setObjectName("basespinboxgroup2");
        for (auto i = 0; i != m_count; ++i)
        {
            flowLayout->addWidget(createWidget(list.at(i)));
        }
        setLayout(flowLayout);
    }

    /// \brief Returns the minimum value applied to all spin boxes.
    T minimum() const
    {
        return m_minimum;
    }

    /// \brief Sets the minimum value on all spin boxes.
    void setMinimum(T minimum)
    {
        m_minimum = minimum;
        auto spinBoxes = findChildren<S *>();
        for (auto *spinBox : spinBoxes)
            spinBox->setMinimum(m_minimum);
    }

    /// \brief Returns the maximum value applied to all spin boxes.
    T maximum() const
    {
        return m_maximum;
    }

    /// \brief Sets the maximum value on all spin boxes.
    void setMaximum(T maximum)
    {
        m_maximum = maximum;
        auto spinBoxes = findChildren<S *>();
        for (auto *spinBox : spinBoxes)
            spinBox->setMaximum(m_maximum);
    }

    /// \brief Returns the single-step increment applied to all spin boxes.
    T singleStep() const
    {
        return m_singleStep;
    }

    /// \brief Sets the single-step increment on all spin boxes.
    void setSingleStep(T singleStep)
    {
        m_singleStep = singleStep;
        auto spinBoxes = findChildren<S *>();
        for (auto *spinBox : spinBoxes)
            spinBox->setSingleStep(m_singleStep);
    }

    /// \brief Returns the current values of all spin boxes as a vector.
    auto value() const
    {
        auto spinBoxes = findChildren<S *>();
        std::vector<T> vector;
        std::transform(spinBoxes.cbegin(), spinBoxes.cend(), std::back_inserter(vector),
            [](const auto *spinBox) { return T(spinBox->value()); });
        return vector;
    }

    /// \brief Sets spin box values from \a array; extra elements are silently ignored.
    void setValue(const std::vector<T> &array)
    {
        auto spinBoxes = findChildren<S *>();
        const int count = std::min(spinBoxes.size(), static_cast<int>(array.size()));
        for (auto i = 0; i < count; ++i)
            spinBoxes.at(i)->setValue(array.at(i));
    }

    /// \brief Sets spin box values from a float vector; extra elements are silently ignored.
    void setValue(const std::vector<float> &array)
    {
        auto spinBoxes = findChildren<S *>();
        const int count = std::min(spinBoxes.size(), static_cast<int>(array.size()));
        for (auto i = 0; i < count; ++i)
            spinBoxes.at(i)->setValue(array.at(i));
    }

    /// \brief Returns the decimal precision applied to all spin boxes.
    int decimals() const
    {
        return m_decimals;
    }

    /// \brief Sets the decimal precision on all spin boxes.
    void setDecimals(int decimals)
    {
        m_decimals = decimals;
        auto spinBoxes = findChildren<S *>();
        for (auto *spinBox : spinBoxes)
            spinBox->setDecimals(m_decimals);
    }

    /// \brief Returns the number of spin boxes in the group.
    int count() const
    {
        return m_count;
    }

private:
    int m_count;
    T m_minimum;
    T m_maximum;
    T m_singleStep;
    int m_decimals;
};

using DoubleSpinBoxGroup = BaseSpinBoxGroup<double, EDoubleSpinBox>;
using SpinBoxGroup = BaseSpinBoxGroup<int, ESpinBox>;
