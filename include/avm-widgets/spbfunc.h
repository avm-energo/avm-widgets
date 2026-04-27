#pragma once

#include <avm-widgets/basespinboxgroup.h>
#include <avm-widgets/edoublespinbox.h>
#include <export.h>

/// \brief Factory and accessor helpers for EDoubleSpinBox and DoubleSpinBoxGroup widgets.
class WD_EXPORT SPBFunc
{
public:
    SPBFunc();

    /// \brief Finds an EDoubleSpinBox by \a spbname inside \a parent.
    [[nodiscard]] static EDoubleSpinBox *spinBox(QWidget *parent, const QString &spbname);
    /// \brief Creates a new EDoubleSpinBox with given range and decimal precision.
    [[nodiscard]] static EDoubleSpinBox *New(
        QWidget *parent, const QString &spbname, const double min, const double max, const int decimals);
    /// \brief Creates a caption label + spin box pair widget.
    [[nodiscard]] static QWidget *newLBL(QWidget *parent, const QString &caption, const QString &spbname,
        const double min, const double max, const int decimals);
    /// \brief Creates a DoubleSpinBoxGroup with \a count auto-numbered spin boxes.
    [[nodiscard]] static DoubleSpinBoxGroup *newGroup(
        QWidget *parent, const QString &spbname, int count, const double min, const double max, const int decimals);
    /// \brief Creates a DoubleSpinBoxGroup with labels taken from \a list.
    [[nodiscard]] static DoubleSpinBoxGroup *newGroup(QWidget *parent, const QString &spbname, const QStringList &list,
        const double min, const double max, const int decimals);
    /// \brief Sets the value of a spin box found by \a spbname.
    static bool setData(const QObject *parent, const QString &spbname, const double &spbvalue);

    /// \brief Sets group spin box values from a fixed-size array \a spbvalue.
    template <size_t N, typename T>
    static bool setGroupData(const QWidget *parent, const QString &spbname, const std::array<T, N> spbvalue)
    {
        auto spbg = dynamic_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
            return false;
        spbg->setValue(std::vector<float>(spbvalue.cbegin(), spbvalue.cend()));
        return true;
    }

    /// \brief Sets group spin box values from a std::vector \a spbvalue.
    template <typename T>
    static bool setGroupData(const QWidget *parent, const QString &spbname, const std::vector<T> &spbvalue)
    {
        auto spbg = dynamic_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
            return false;
        spbg->setValue(spbvalue);
        return true;
    }

    /// \brief Sets group spin box values from a QList \a spbvalue.
    template <typename T>
    static bool setGroupData(const QWidget *parent, const QString &spbname, const QList<T> &spbvalue)
    {
        auto spbg = dynamic_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
            return false;
        spbg->setValue(std::vector<T>(spbvalue.cbegin(), spbvalue.cend()));
        return true;
    }

    /// \brief Reads the spin box value into \a spbvalue; returns false if the widget is not found.
    template <typename T> static bool data(const QObject *parent, const QString &spbname, T &spbvalue)
    {
        auto spb = parent->findChild<EDoubleSpinBox *>(spbname);
        if (spb == nullptr)
        {
            spbvalue = 0;
            return false;
        }
        spbvalue = spb->value();
        return true;
    }

    /// \brief Returns the spin box value cast to \a T; logs a warning and returns 0 if not found.
    template <typename T> static T data(const QObject *parent, const QString &spbname)
    {
        auto spb = parent->findChild<EDoubleSpinBox *>(spbname);
        if (spb == nullptr)
        {
            qWarning() << "No spinbox " << spbname;
            return 0;
        }
        return T(spb->value());
    }

    /// \brief Reads group spin box values into a fixed-size array; extra group elements are ignored.
    template <size_t N, typename T>
    static bool groupData(const QWidget *parent, const QString &spbname, std::array<T, N> &spbvalue)
    {
        auto spbg = dynamic_cast<DoubleSpinBoxGroup *>(parent->findChild<QWidget *>(spbname));
        if (spbg == nullptr)
        {
            spbvalue = {};
            return false;
        }
        auto vector = spbg->value();
        std::copy_n(vector.cbegin(), std::min(N, vector.size()), spbvalue.begin());
        // spbvalue = spbg->value();
        return true;
    }
};
